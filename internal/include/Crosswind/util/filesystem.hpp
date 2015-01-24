#pragma once 

#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <unordered_set>
#include <stdexcept>

#if defined (WIN32) //TODO implement std::filesystem whenever the commitee releases it.
    #if _MSC_VER >= 1600
        #include <Crosswind/private/dirent.h>
    #elif __MINGW32__
        #include <dirent.h>
    #endif
#else
#include <dirent.h>
#endif

namespace cw{

    class filepath{

    };

	class filesystem{
    public:
        static void addDirectory(const std::string& directory, bool recursively = false){

            push_directory(directory);

            if(recursively){ addDirectoryRecursively(directory); }

        }


		static bool exists (const std::string& name, const std::string& path = "") {

            //TODO test with Visual Studio.
            auto result = std::find_if(directories.begin(), directories.end(),
                    [&](std::string const& directory)  {
                        return path != "" ?
                                is_file(directory + "/" + path + "/" + name) ||
                                is_dir(directory + "/" + path + "/" + name)
                                :
                                is_file(directory + "/" + name) ||
                                is_dir(directory + "/" + name);
                    });

            if(result != std::end(directories)){
                return true;
            } else {
                return false;
            }
		}

        static std::string get_file_path(const std::string& file, const std::string& path = ""){

            //TODO optimize path != ""
            if(exists(file, path)){
                auto result = std::find_if(directories.begin(), directories.end(),
                        [&](std::string const& directory)  {
                            //TODO test with Visual Studio.
                            if(path != ""){
                                return is_file(directory + "/" + path + "/" + file);
                            } else {
                                return is_file(directory + "/" + file);
                            }
                        });

                if(result != std::end(directories)){
                    return path != "" ? *result + "/" + path + "/" + file : *result + "/" + file;
                } else {
                    throw std::runtime_error(file + std::string(": Not a file."));
                }
            } else {
                throw std::runtime_error(file + std::string(": Does not exist."));
            }
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


    private:
        static void push_directory(const std::string& directory){
            if(std::find(directories.begin(), directories.end(), directory) == directories.end())
            {
                directories.push_front(directory);
            }
        }


        static void addDirectoryRecursively(std::string parent) {

            if(is_dir(parent)){

                push_directory(parent);

                if (DIR *dp = opendir(parent.c_str()))
                {
                    while (struct dirent *ep = readdir(dp))
                        if (ep->d_name[0] != '.')
                            addDirectoryRecursively(parent + "/" + ep->d_name);
                    closedir(dp);
                }
                else
                    throw std::runtime_error(parent + std::string(": Couldn't open the directory."));
            }

        }


    private:
        static std::forward_list<std::string> directories;
	};


    std::forward_list<std::string> filesystem::directories;
}