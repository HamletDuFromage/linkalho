#ifndef __LINKUSER_FILE_OPERATIONS_HPP__
#define __LINKUSER_FILE_OPERATIONS_HPP__

#include <filesystem>
#include <vector>

bool init_dirs();
void link_account();
void unlink_account();
void restore_backup(const std::string&);
std::vector<std::filesystem::path> get_dir_contents(const std::string&, const std::string& extension="", bool onlydirs=false);

#endif // __LINKUSER_FILE_OPERATIONS_HPP__
