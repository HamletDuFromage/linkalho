#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include <borealis.hpp>
#include <string>
#include <sys/stat.h>
#include "confirm_page.hpp"
#include "worker_page.hpp"
#include "file_operations.hpp"
#include "constants.hpp"
#include "custom_style.hpp"
#include "custom_theme.hpp"
#include "progress_event.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    // Init the app
    // brls::Logger::setLogLevel(brls::LogLevel::DEBUG);

    if (!brls::Application::init("link-user", CustomStyle::custom_style(), CustomTheme::custom_theme()))
    {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    brls::AppletFrame* rootFrame = new brls::AppletFrame(false, false);
    rootFrame->setTitle(string(APP_TITLE) + " v" + string(APP_VERSION));

    brls::List* operationList = new brls::List();

    brls::ListItem* linkItem = new brls::ListItem("Link all accounts");
    linkItem->getClickEvent()->subscribe([](brls::View* view) {
        brls::StagedAppletFrame* stagedFrame = new brls::StagedAppletFrame();
        stagedFrame->setTitle("Link all accounts");

        stagedFrame->addStage(
            new ConfirmPage(stagedFrame, "Linking all accounts will overwrite all previous links.\nIf you had any previosly linked NNID account, it will be erased!")
        );
        stagedFrame->addStage(
            new WorkerPage(stagedFrame, "Linking...", [](){
                link_account();
            })
        );
        stagedFrame->addStage(
            new ConfirmPage(stagedFrame, "Accounts linked!", true)
        );

        brls::Application::pushView(stagedFrame);
        stagedFrame->registerAction("", brls::Key::PLUS, []{return true;}, true);
        stagedFrame->updateActionHint(brls::Key::PLUS, ""); // make the change visible
        stagedFrame->registerAction("", brls::Key::B, []{return true;}, true);
        stagedFrame->updateActionHint(brls::Key::B, ""); // make the change visible
    });
    operationList->addView(linkItem);

    brls::ListItem* unlinkItem = new brls::ListItem("Unlink all accounts");
    unlinkItem->getClickEvent()->subscribe([](brls::View* view) {
        brls::StagedAppletFrame* stagedFrame = new brls::StagedAppletFrame();
        stagedFrame->setTitle("Unlink all accounts");

        stagedFrame->addStage(
            new ConfirmPage(stagedFrame, "Unlinking accounts will reset all users.\nIf you had any previosly linked NNID account, it will be erased!")
        );
        stagedFrame->addStage(
            new WorkerPage(stagedFrame, "Unlinking...", [](){
                unlink_account();
            })
        );
        stagedFrame->addStage(
            new ConfirmPage(stagedFrame, "Accounts unlinked!", true)
        );

        brls::Application::pushView(stagedFrame);
        stagedFrame->registerAction("", brls::Key::PLUS, []{return true;}, true);
        stagedFrame->updateActionHint(brls::Key::PLUS, ""); // make the change visible
        stagedFrame->registerAction("", brls::Key::B, []{return true;}, true);
        stagedFrame->updateActionHint(brls::Key::B, ""); // make the change visible
    });
    operationList->addView(unlinkItem);

    struct stat buffer;
    bool backup_exists = (stat(RESTORE_FILE_PATH, &buffer) == 0);
    if (backup_exists) {
        brls::ListItem* restoreItem = new brls::ListItem("Restore backup");
        restoreItem->getClickEvent()->subscribe([](brls::View* view) {
            brls::StagedAppletFrame* stagedFrame = new brls::StagedAppletFrame();
            stagedFrame->setTitle("Restore backup");

            stagedFrame->addStage(
                new ConfirmPage(stagedFrame, "Restoring this backup WILL overwrite all files!\n\nMake sure the backup is valid as it will overwrite the console's partition files and might cause your Switch to stop booting!")
            );
            stagedFrame->addStage(
                new WorkerPage(stagedFrame, "Restoring...", [](){
                    restore_backup(RESTORE_FILE_PATH);
                })
            );
            stagedFrame->addStage(
                new ConfirmPage(stagedFrame, "Backup restored!", true)
            );

            brls::Application::pushView(stagedFrame);
            stagedFrame->registerAction("", brls::Key::PLUS, []{return true;}, true);
            stagedFrame->updateActionHint(brls::Key::PLUS, ""); // make the change visible
            stagedFrame->registerAction("", brls::Key::B, []{return true;}, true);
            stagedFrame->updateActionHint(brls::Key::B, ""); // make the change visible
        });
        operationList->addView(restoreItem);
    } else {
        brls::ListItem* dialogItem = new brls::ListItem("Restore backup");
        dialogItem->getClickEvent()->subscribe([](brls::View* view) {
            brls::Dialog* dialog = new brls::Dialog("To restore, please place yout backup file into\n" + string(RESTORE_FILE_PATH) + "\n\nMake sure the backup is valid as it will overwrite the console's partition files and might cause your Switch to stop booting!");
            dialog->addButton("Close", [dialog](brls::View* view) {
                dialog->close();
            });
            dialog->open();
            dialog->registerAction("", brls::Key::PLUS, []{return true;}, true);
            dialog->updateActionHint(brls::Key::PLUS, ""); // make the change visible
        });
        operationList->addView(dialogItem);
    }


    rootFrame->setContentView(operationList);
    brls::Application::pushView(rootFrame);
    rootFrame->registerAction("", brls::Key::MINUS, []{return true;}, true);
    rootFrame->updateActionHint(brls::Key::MINUS, ""); // make the change visible

    pmshellInitialize();
    init_dirs();

    // Run the app
    while (brls::Application::mainLoop())
        ;

    pmshellExit();

    // Exit
    return EXIT_SUCCESS;
}
