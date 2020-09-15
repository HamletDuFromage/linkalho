#include <borealis/application.hpp>
#include <switch.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <filesystem>
#include <sstream>
#include <vector>
#include <fstream>
#include "zipper.h"
#include "unzipper.h"
#include "constants.hpp"
#include "generator.hpp"
#include "progress_event.hpp"

using namespace std;
using namespace zipper;

void shutdown_account()
{
    cout << "Attempting to shut down account and olsc... ";
    bool success = R_SUCCEEDED(pmshellTerminateProgram(0x010000000000001E));
    cout << (success ? "Succeess!" : "Failed! Already terminated?") << endl;
    //helps a bit
    pmshellTerminateProgram(0x010000000000003E);
}

vector<filesystem::path> get_dir_contents(const string& path, const string& extension, bool onlydirs=false)
{
    vector<filesystem::path> contents;
    bool filtered = extension.length() > 0;
    for (auto& entry: filesystem::recursive_directory_iterator(path)) {
        if (!entry.is_regular_file()) {
            if (onlydirs || !filtered) {
                contents.push_back(entry.path());
            }
            continue;
        }
        if (onlydirs || entry.path().extension().string() == "")
            continue;
        if (!filtered || entry.path().extension().string() == extension) {
            contents.push_back(entry.path());
        }
    }
    return contents;
}

void cleanup_mac_files(const string& path)
{
    for (auto& entry: filesystem::recursive_directory_iterator(path)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        if (entry.path().filename().string() == ".DS_Store") {
            filesystem::remove_all(entry.path().string());
        }
    }
}

bool init_dirs()
{
    try
    {
        filesystem::create_directories(BACKUP_PATH);
        filesystem::create_directories(RESTORE_FILE_DIR);
        return true;
    }
    catch (exception& e) // Not using filesystem_error since bad_alloc can throw too.
    {
        cout << e.what() << endl;
        brls::Application::crash(string("Failed! ") + e.what());
    }
    return false;
}

FsFileSystem mount_save_data()
{
    FsFileSystem acc;
#ifndef DEBUG
    shutdown_account();
    cout << "Attempting to mount savedata... ";
    if(R_SUCCEEDED(fsOpen_SystemSaveData(&acc, FsSaveDataSpaceId_System, 0x8000000000000010, (AccountUid) {0}))) {
        cout << "Succeess!" << endl;
        fsdevMountDevice("account", acc);
    } else {
        cout << "Failed!" << endl;
    }
#endif
    return acc;
}

void unmount_save_data(FsFileSystem& acc, bool commit=false)
{
#ifndef DEBUG
    if (commit) {
        fsdevCommitDevice("account");
    }
    fsdevUnmountDevice("account");
    fsFsClose(&acc);
#endif
}

void execute_backup(const string& reason)
{
    cleanup_mac_files(RESTORE_PATH);

    time_t t = time(nullptr);
    tm tm = *localtime(&t);
    stringstream backup_file;
    backup_file << BACKUP_PATH << "backup_profiles_" << put_time(&tm, "%Y%m%d_%H%M%S") << "[" << reason << "].zip";
    cout << "Creating backup..." << endl << endl;
    Zipper zipper(backup_file.str());
    //auto flags = (Zipper::zipFlags::Better | Zipper::zipFlags::SaveHierarchy);
    zipper.add(string(ACCOUNT_PATH)+"/registry.dat");
    zipper.add(string(ACCOUNT_PATH)+"/avators");
    zipper.add(string(ACCOUNT_PATH)+"/baas");
    zipper.add(string(ACCOUNT_PATH)+"/nas");
    zipper.close();
    cout << "Backup created in " << BACKUP_PATH << endl;
}

void restore_backup(const string& backup_fullpath)
{
    try {
        ProgressEvent::instance().reset();
        ProgressEvent::instance().setTotalSteps(7);

        FsFileSystem acc = mount_save_data();
        ProgressEvent::instance().setStep(1);

        execute_backup("restore");
        ProgressEvent::instance().setStep(2);
        cout << endl << endl  << "Restoring backup... ";

        auto baas_dir = string(RESTORE_PATH) + "/baas";
        filesystem::remove_all(baas_dir);
        ProgressEvent::instance().setStep(3);

        auto nas_dir = string(RESTORE_PATH) + "/nas";
        filesystem::remove_all(nas_dir);
        ProgressEvent::instance().setStep(4);

        auto avators_dir = string(RESTORE_PATH) + "/avators";
        for (auto& jpg_file: get_dir_contents(avators_dir, ".jpg")) {
            filesystem::remove_all(jpg_file.string());
        }
        ProgressEvent::instance().setStep(5);

        Unzipper unzipper(backup_fullpath);
        unzipper.extract(RESTORE_PATH);
        unzipper.close();
        ProgressEvent::instance().setStep(6);
        cout << "Success!" << endl;

        unmount_save_data(acc, true);
        ProgressEvent::instance().setStep(7);
    }
    catch (exception& e) // Not using filesystem_error since bad_alloc can throw too.
    {
        cout << "Failed! " << e.what() << endl;
        brls::Application::crash(string("Failed! ") + e.what());
    }
}

void link_account()
{
    try {
        ProgressEvent::instance().reset();
        ProgressEvent::instance().setTotalSteps(6);

        FsFileSystem acc = mount_save_data();
        ProgressEvent::instance().setStep(1);

        execute_backup("link");
        ProgressEvent::instance().setStep(2);
        cout << endl << endl  << "Linking accounts... ";

        auto baas_dir = string(ACCOUNT_PATH) + "/baas";
        // cout << "create=[" << baas_dir << "]" << endl;
        filesystem::create_directories(baas_dir);
        filesystem::remove_all(baas_dir);
        ProgressEvent::instance().setStep(3);

        auto nas_dir = string(ACCOUNT_PATH) + "/nas";
        // cout << "create=[" << nas_dir << "]" << endl;
        filesystem::create_directories(nas_dir);
        filesystem::remove_all(nas_dir);
        ProgressEvent::instance().setStep(4);

        for (auto& entry: get_dir_contents(ACCOUNT_PATH, ".jpg")) {

            auto linker_file = baas_dir+"/"+entry.stem().string()+".dat";
            Generator::instance().write_baas(linker_file);

            auto profile_dat_filename = nas_dir + "/" + Generator::instance().nas_id_str() + ".dat";
            Generator::instance().write_profile_dat(profile_dat_filename);

            // auto profile = stringReplace(PROFILE, "#NAS_ID#", nas_id_ss.str());
            auto profile_json_filename = nas_dir + "/" + Generator::instance().nas_id_str() + "_user.json";
            Generator::instance().write_profile_json(profile_json_filename);
        }
        ProgressEvent::instance().setStep(5);
        cout << "Success!" << endl;

        unmount_save_data(acc, true);
        ProgressEvent::instance().setStep(6);
    }
    catch (exception& e) // Not using filesystem_error since bad_alloc can throw too.
    {
        cout << "Failed! " << e.what() << endl;
        brls::Application::crash(string("Failed! ") + e.what());
    }
}

void unlink_account()
{
    try {
        ProgressEvent::instance().reset();
        ProgressEvent::instance().setTotalSteps(5);

        FsFileSystem acc = mount_save_data();
        ProgressEvent::instance().setStep(1);

        execute_backup("unlink");
        ProgressEvent::instance().setStep(2);
        cout << endl << endl  << "Unlinking accounts... ";

        auto baas_dir = string(ACCOUNT_PATH) + "/baas";
        filesystem::remove_all(baas_dir);
        ProgressEvent::instance().setStep(3);

        auto nas_dir = string(ACCOUNT_PATH) + "/nas";
        filesystem::remove_all(nas_dir);
        ProgressEvent::instance().setStep(4);

        cout << "Success!" << endl;
        unmount_save_data(acc, true);
        ProgressEvent::instance().setStep(5);
    }
    catch (exception& e) // Not using filesystem_error since bad_alloc can throw too.
    {
        cout << "Failed! " << e.what() << endl;
        brls::Application::crash(string("Failed! ") + e.what());
    }
}