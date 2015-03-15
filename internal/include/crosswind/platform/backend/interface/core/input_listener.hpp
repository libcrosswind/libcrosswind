#pragma once

#include <string>

#include <glm/glm.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace interface{
namespace core{

	class input_listener;

}// namespace core
}// namespace interface
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::interface::core::input_listener{
public:
	virtual bool is_key_down(const std::string& key) = 0;
    virtual glm::vec2 get_mouse_coordinates() = 0;
	virtual void update() = 0;

protected:
	input_listener(){

	}

    std::map<std::string, bool> key_map;
    glm::vec2 mouse_coordinates;

   // functional::delegate<void, std::string> on_key_down;
};// class input_listener