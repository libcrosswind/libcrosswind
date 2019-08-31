#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdexcept>
#include <forward_list>
#include <regex>

#if defined (WIN32) //TODO implement std::filesystem whenever the commitee releases it.
    #if _MSC_VER >= 1600
        #include <crosswind/trivial/filesystem/dirent.h>
    #elif __MINGW32__
        #include <dirent.h>
    #endif
#else
#include <dirent.h>
#include <unistd.h>

#endif

#include "crosswind/platform/filesystem.hpp"

#define MAXPATHLEN 512

std::string cw::platform::filesystem::get_cwd(){

    char temp[MAXPATHLEN];
    return ( getcwd(temp, MAXPATHLEN) ? std::string( temp ) : std::string("") );

}

#undef MAXPATHLEN

std::vector<std::string> cw::platform::filesystem::get_folder_content(const std::string& folder){

    std::vector<std::string> content;

    if(is_dir(folder)){
        if (DIR *dp = opendir(folder.c_str()))
        {
            while (struct dirent *ep = readdir(dp)) {
                content.push_back(ep->d_name);
            }

            closedir(dp);
        }

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
