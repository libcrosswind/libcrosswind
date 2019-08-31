#pragma once

#include <vector>
#include <string>
#include <forward_list>

namespace cw{
namespace platform{

class filesystem{
public:

    std::string get_cwd();

    std::vector<std::string> get_folder_content(const std::string& folder);

    bool is_file(const std::string& file);

    bool is_dir(const std::string& dir);

};// class filesystem

}// namespace platform
}// namespace cw
