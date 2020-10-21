#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdexcept>
#include <forward_list>
#include <regex>

#include <filesystem>

#include "crosswind/platform/filesystem.hpp"

std::string cw::platform::filesystem::get_cwd(){

    return std::filesystem::current_path().string();
}

std::vector<std::string> cw::platform::filesystem::get_folder_content(const std::string& folder){

    std::vector<std::string> content;

    if(is_dir(folder)){
        for (auto& p : std::filesystem::directory_iterator(folder))
            content.push_back(p.path().string());

    } else {
        throw std::runtime_error(folder + std::string(": Not a directory."));
    }

    return content;

}


bool cw::platform::filesystem::is_file(const std::string& file){

    struct stat s;
    stat(file.c_str(), &s);
    return (s.st_mode & S_IFREG)!=0;

}

bool cw::platform::filesystem::is_dir(const std::string& dir){

    struct stat s;
    stat(dir.c_str(), &s);
    return (s.st_mode & S_IFDIR)!=0;

}
