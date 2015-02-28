#pragma once 

#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdexcept>
#include <forward_list>
#include <regex>

#include <crosswind/concurrent/mutex_property.hpp>

#if defined (WIN32) //TODO implement std::filesystem whenever the commitee releases it.
    #if _MSC_VER >= 1600
        #include <crosswind/trivial/filesystem/dirent.h>
    #elif __MINGW32__
        #include <dirent.h>
    #endif
#else
#include <dirent.h>
#endif

namespace cw{
namespace platform{

    class filesystem;

}// namespace platform
}// namespace cw


class cw::platform::filesystem{
public:
    static void add_directory(const std::string& directory, bool recursively = false){

        push_directory(directory);

        if(recursively){ add_recursively(directory); }

    }

	static bool exists (const std::string& filepath) {

        std::vector<std::string> path = split(filepath);

        bool search_result  = false;
        auto& local_directories = directories.acquire();

        //TODO test with Visual Studio.
        auto result = std::find_if(local_directories.begin(), local_directories.end(),
                [&](std::string const& directory)  {
                    std::cout << directory << std::endl;
                    return path[0] != "" ?
                            is_file(directory + "/" + path[0] + "/" + path[1]) ||
                            is_dir(directory + "/" + path[0] + "/" + path[1])
                            :
                            is_file(directory + "/" + path[1]) ||
                            is_dir(directory + "/" + path[1]);
                });

        if(result != std::end(local_directories)){
            search_result = true;
        } else {
            search_result = false;
        }

        directories.release();

        return search_result;

    }

    static std::string get_file_path(const std::string& filepath){

        std::vector<std::string> path = split(filepath);
        std::string path_string = "";

        if(exists(filepath)){

            auto& local_directories = directories.acquire();

            auto result = std::find_if(local_directories.begin(), local_directories.end(),
                    [&](std::string const& directory)  {
                        //TODO test with Visual Studio.
                        if(path[0] != ""){
                            return is_file(directory + "/" + path[0] + "/" + path[1]);
                        } else {
                            return is_file(directory + "/" + path[1]);
                        }
                    });

            if(result != std::end(local_directories)){
                path_string = path[0] != "" ? *result + "/" + path[0] + "/" + path[1] : *result + "/" + path[1];
            } else {
                path_string = filepath + ": Is not a file";
            }

            directories.release();

        } else {
            path_string = filepath + ": Does not exist";
        }

        return path_string;
    }


private:
    static bool is_file(const std::string& file){
        struct stat s;
        stat(file.c_str(), &s);
        return (s.st_mode & S_IFREG)!=0;
    }

    static bool is_dir(const std::string& dir){
        struct stat s;
        stat(dir.c_str(), &s);
        return (s.st_mode & S_IFDIR)!=0;
    }

    static std::vector<std::string> split(const std::string& path){
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

private:
    static void push_directory(const std::string& directory){
        auto& local_directories = directories.acquire();
        if(std::find(local_directories.begin(), local_directories.end(), directory) == local_directories.end())
        {
            local_directories.push_front(directory);
        }

        directories.release();
    }


    static void add_recursively(const std::string& parent) {

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


private:
    static concurrent::mutex_property<std::forward_list<std::string> > directories;
};

cw::concurrent::mutex_property<std::forward_list<std::string> > cw::platform::filesystem::directories;


