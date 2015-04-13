#pragma once 

#include <vector>
#include <string>
#include <forward_list>

namespace cw{
namespace platform{

class filesystem{
public:
    void add_directory(const std::string& directory, bool recursively = false);

	bool exists (const std::string& filepath);

    std::string get_file_path(const std::string& filepath);

    std::string get_cwd();

    std::vector<std::string> get_folder_content(const std::string& folder);

    bool is_file(const std::string& file);
    
    bool is_dir(const std::string& dir);

    std::vector<std::string> split(const std::string& path);

private:
    void push_directory(const std::string& directory);

    void add_recursively(const std::string& parent);

    std::forward_list<std::string> directories;

};// class filesystem

}// namespace platform
}// namespace cw
