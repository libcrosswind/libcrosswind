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

void cw::platform::filesystem::add_directory(const std::string& directory, bool recursively){

        push_directory(directory);

        if(recursively){ 
        	add_recursively(directory); 
        }

}

bool cw::platform::filesystem::exists(const std::string& filepath) {

    std::vector<std::string> path = split(filepath);

    bool search_result  = false;

    //TODO test with Visual Studio.
    auto result = std::find_if(directories.begin(), directories.end(),
            [&](std::string const& directory)  {
                return path[0] != "" ?
                        is_file(directory + "/" + path[0] + "/" + path[1]) ||
                        is_dir(directory + "/" + path[0] + "/" + path[1])
                        :
                        is_file(directory + "/" + path[1]) ||
                        is_dir(directory + "/" + path[1]);
            });

    if(result != std::end(directories)){
        search_result = true;
    } else {
        search_result = false;
    }

    if(!search_result){
        search_result = is_file(filepath) || is_dir(filepath);
    }

    return search_result;

}

std::string cw::platform::filesystem::get_file_path(const std::string& filepath){

    std::vector<std::string> path = split(filepath);
    std::string path_string = "";

    if(exists(filepath)){

        auto result = std::find_if(directories.begin(), directories.end(),
                [&](std::string const& directory)  {
                    //TODO test with Visual Studio.
                    if(path[0] != ""){
                        return is_file(directory + "/" + path[0] + "/" + path[1]) || is_file(filepath);
                    } else {
                        return is_file(directory + "/" + path[1]);
                    }
                });

        if(result != std::end(directories)){
            if(is_file(filepath)){
                path_string = filepath;
            } else{
                path_string = path[0] != "" ? *result + "/" + path[0] + "/" + path[1] : *result + "/" + path[1];
            }

        } else {
            path_string = filepath + ": Is not a file";
        }

    } else {
        path_string = filepath + ": Does not exist";
    }

    return path_string;

}

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

std::vector<std::string> cw::platform::filesystem::split(const std::string& path){

    std::string filepath = path;
    
    if(filepath.substr(filepath.size() - 1, filepath.size()).compare("/") == 0){
        filepath  = filepath.substr(0, filepath.size() - 1);
    }

    std::regex path_regex("^(.+/)(.+)$");
    std::smatch sm;

    std::vector<std::string> result(2);

    result[0] = "";
    result[1] = filepath;

    if (std::regex_match(filepath, sm, path_regex))
    {
        result[0] = sm[1];
        result[1] = sm[2];
    }

    return result;

}

void cw::platform::filesystem::push_directory(const std::string& directory){

    if(std::find(directories.begin(), directories.end(), directory) == directories.end())
    {
        directories.push_front(directory);
    }

}


void cw::platform::filesystem::add_recursively(const std::string& parent) {

    if(is_dir(parent)){

        push_directory(parent);

        if (DIR *dp = opendir(parent.c_str()))
        {
            while (struct dirent *ep = readdir(dp))
                if (ep->d_name[0] != '.')
                    add_recursively(parent + "/" + ep->d_name);
            closedir(dp);
        }
        else
            throw std::runtime_error(parent + std::string(": Couldn't open the directory."));
    }

} 