#pragma once

#include <map>
#include <string>
#include <functional>

#include "glm/glm.hpp"

#include "crosswind/modules/functional/delegate.hpp"

namespace cw{
namespace platform{

class input{
public:
    input();

	bool is_key_down(const std::string& key);

    glm::vec2 get_mouse_coordinates();

    void add_on_key_down_listener(const std::function<void(const std::string&)>& listener);
/*
    void remove_on_key_down_listener(const std::function<void(const std::string&)>& listener);
*/
    void on_key_down(const std::string& key);

	void update(const float& delta);

private:
    std::map<std::string, bool> key_map;
    glm::vec2 mouse_coordinates;
    functional::delegate<void, const std::string&> ok_key_down_listeners;
    float delta_count;
    bool buffering;
    std::string last_key;

};// class input

}// namespace platform
}// namespace cw