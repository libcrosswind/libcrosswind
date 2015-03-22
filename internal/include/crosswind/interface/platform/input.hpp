#pragma once

#include <string>
#include <map>

#include <glm/glm.hpp>

namespace cw{
namespace interface{
namespace platform{

	class input;

}// namespace platform
}// namespace interface
}// namespace cw

class cw::interface::platform::input{
public:
	input(){

	}

	virtual bool is_key_down(const std::string& key) = 0;
    virtual glm::vec2 get_mouse_coordinates() = 0;
	virtual void update() = 0;

protected:
    std::map<std::string, bool> key_map;
    glm::vec2 mouse_coordinates;

};// class input