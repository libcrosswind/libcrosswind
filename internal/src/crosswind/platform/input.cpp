#include <cstdint>

#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_mouse.h"

#include "crosswind/platform/input.hpp"

// extern declarations
namespace cw{
namespace platform{

#ifdef __cplusplus
extern "C" {
#endif
 
    extern DECLSPEC void SDL_GetDefaultKeymap(SDL_Keycode * keymap);

#ifdef __cplusplus
    }
#endif

}// namespace platform
}// namespace cw


cw::platform::input::input(){

    int array_counter = 0;

    int32_t keymap[SDL_NUM_SCANCODES];

    SDL_GetDefaultKeymap(keymap);

    while(array_counter < SDL_NUM_SCANCODES){

        std::string key_name = SDL_GetKeyName(keymap[array_counter]);
          if(!key_name.empty())
              key_map[key_name] = false;

        array_counter++;
    }

    key_map["mouse_left"] = false;
    key_map["mouse_middle"] = false;
    key_map["mouse_right"] = false;

    delta_count = 0.0f;
    buffering = false;
    last_key = "";
}

bool cw::platform::input::is_key_down(const std::string& key){

	return key_map[key];

}

glm::vec2 cw::platform::input::get_mouse_coordinates(){

    return mouse_coordinates;

}

void cw::platform::input::add_on_key_down_listener(const std::function<void(const std::string&)>& listener){
    ok_key_down_listeners += listener;
}

/*void cw::platform::input::remove_on_key_down_listener(const std::function<void(const std::string&)>& listener){
    ok_key_down_listeners -= listener;
}*/

void cw::platform::input::on_key_down(const std::string& key){

    if(delta_count <= 0.50f){
        if(!buffering){
            buffering = true;
            ok_key_down_listeners(key);
        }
    } else {
        buffering = false;
    }

    if(buffering){
        if(last_key != key){
            buffering = false;
            delta_count = 0.0f;
        }
    } else {
       ok_key_down_listeners(key);
    }


}

void cw::platform::input::update(const float& delta){

	const uint8_t* state = SDL_GetKeyboardState(NULL);

	for(auto& key : key_map){
		if((key_map[key.first] = state[SDL_GetScancodeFromName(key.first.c_str())]) == true){
            on_key_down(key.first);
        }
	}

    int x, y;

    auto mouse_flags = SDL_GetMouseState(&x, &y);

    key_map["mouse_left"] = mouse_flags & SDL_BUTTON(SDL_BUTTON_LEFT);
    key_map["mouse_middle"] = mouse_flags & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    key_map["mouse_right"] = mouse_flags & SDL_BUTTON(SDL_BUTTON_RIGHT);

    mouse_coordinates.x = x;
    mouse_coordinates.y = y;
}
 