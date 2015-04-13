#pragma once

#include <map>
#include <string>

#include "glm/glm.hpp"

namespace cw{
namespace platform{

class input{
public:
    input();

	bool is_key_down(const std::string& key);

    glm::vec2 get_mouse_coordinates();

	void update();

private:
    std::map<std::string, bool> key_map;
    glm::vec2 mouse_coordinates;

};// class input

}// namespace platform
}// namespace cw