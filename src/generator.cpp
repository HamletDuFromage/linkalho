#include <random>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "constants.hpp"
#include "generator.hpp"

#include <iostream>

using namespace std;

static auto BAAS_HEADER1    = 0xA5D192EA40AD1304;
static auto BAAS_HEADER2    = 0x0000006E00000001;
static auto BAAS_HEADER3    = 0x0000000100000001;
static auto PROFILE = R"({"id":"#NAS_ID#","language":"en-US","timezone":"Europe/Lisbon","country":"PT","analyticsOptedIn":false,"gender":"male","emailOptedIn":false,"birthday":"1980-01-01","isChild":false,"email":"•","screenName":"•","region":"","loginId":"•","nickname":"•","isNnLinked":false,"isTwitterLinked":false,"isFacebookLinked":false,"isGoogleLinked":false})";

#ifdef USE_GENERATORS
static mt19937_64 engine(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());

const string generate_random_alphanumeric_string(size_t len)
{
    static constexpr auto chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    uniform_int_distribution<size_t> dist(0, strlen(chars) - 1);
    auto result = string(len, '\0');
    generate_n(begin(result), len, [&]() { return chars[dist(engine)]; });
    return result;
}

unsigned long generate_bytes()
{
    uniform_int_distribution<unsigned long> byte_generator(0x0UL, 0xFFFFFFFFFFFFFFFF);
    return byte_generator(engine);
}
#endif

unsigned long generate_nas_id()
{
#ifdef USE_GENERATORS
    return generate_bytes();
#else
    return 0xF12E677EB4021A81UL;
#endif
}

unsigned long generate_baas_user_id()
{
#ifdef USE_GENERATORS
    return generate_bytes();
#else
    return 0xDEADC0DE000B00B5UL;
#endif
}

const string generate_baas_user_password()
{
#ifdef USE_GENERATORS
    return generate_random_alphanumeric_string(40);
#else
    return "NRwtxRNkYIBE6eWoTG5gM4ykMRoYXOdRZhAWC4IF";
#endif
}

const string generate_profile_dat()
{
#ifdef USE_GENERATORS
    return generate_random_alphanumeric_string(128);
#else
    return string(127, ' ') + '2';
#endif
}

string string_replace(const string& str, const string& from, const string& to) {
    string str_copy = str;
    size_t start_pos = str_copy.find(from);
    if(start_pos == string::npos)
        return str;
    str_copy.replace(start_pos, from.length(), to);
    return str_copy;
}

Generator::Generator()
{
    _baas_user_id = generate_baas_user_id();
    _nas_id = generate_nas_id();
    stringstream nas_id_ss;
    nas_id_ss << std::hex << _nas_id;
    _nas_id_str = nas_id_ss.str();
}

const string& Generator::nas_id_str() {
    return _nas_id_str;
}


void Generator::write_baas(const string& fullpath)
{
    ofstream out_stream(fullpath, ios::binary);
    out_stream.write(reinterpret_cast<char*>(&BAAS_HEADER1), sizeof(BAAS_HEADER1));
    out_stream.write(reinterpret_cast<char*>(&BAAS_HEADER2), sizeof(BAAS_HEADER2));
    out_stream.write(reinterpret_cast<char*>(&_nas_id), sizeof(_nas_id));
    out_stream.write(reinterpret_cast<char*>(&BAAS_HEADER3), sizeof(BAAS_HEADER3));
    out_stream.write(reinterpret_cast<char*>(&_baas_user_id), sizeof(_baas_user_id));
    out_stream << generate_baas_user_password();
}

void Generator::write_profile_dat(const string& fullpath)
{
    ofstream out_stream(fullpath, ios::binary);
    out_stream << generate_profile_dat();
}

void Generator::write_profile_json(const string& fullpath)
{
    ofstream out_stream(fullpath, ios::binary);
    out_stream << string_replace(PROFILE, "#NAS_ID#", _nas_id_str);
}
