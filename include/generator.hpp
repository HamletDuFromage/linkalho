#ifndef __LINKUSER_GENERATOR_HPP__
#define __LINKUSER_GENERATOR_HPP__

#include <string>

class Generator{
private:
    Generator(); // Disallow instantiation outside of the class.

    unsigned long _nas_id;
    std::string _nas_id_str;
    unsigned long _baas_user_id;

public:
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator &) = delete;
    Generator(Generator &&) = delete;
    Generator & operator=(Generator &&) = delete;

    static auto& instance(){
        static Generator gen;
        return gen;
    }

    const std::string& nas_id_str();
    void write_baas(const std::string& fullpath);
    void write_profile_dat(const std::string& fullpath);
    void write_profile_json(const std::string& fullpath);

};

#endif  // __LINKUSER_GENERATOR_HPP__