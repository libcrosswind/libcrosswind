#pragma once

#include <string>
#include <map>

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

#include <crosswind/platform/backend/interface/core/input_listener.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace sdl{
namespace core{
namespace
{
#ifdef __cplusplus
	extern "C" {

#endif

    extern DECLSPEC void SDL_GetDefaultKeymap(SDL_Keycode * keymap);

#ifdef __cplusplus
    }
#endif
}

	class input_listener;

}// namespace core
}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw


class cw::platform::backend::sdl::core::input_listener: public cw::platform::backend::interface::core::input_listener{
public:
    input_listener(){

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

    }

	virtual bool is_key_down(const std::string& key){

		return key_map[key];

	}

    virtual glm::vec2 get_mouse_coordinates(){
        return mouse_coordinates;
    }

	virtual void update(){

		const uint8_t* state = SDL_GetKeyboardState(NULL);

		for(auto& key : key_map){
			key_map[key.first] = state[SDL_GetScancodeFromName(key.first.c_str())];
		}

        int x, y;

        auto mouse_flags = SDL_GetMouseState(&x, &y);

        key_map["mouse_left"] = mouse_flags & SDL_BUTTON(SDL_BUTTON_LEFT);
        key_map["mouse_middle"] = mouse_flags & SDL_BUTTON(SDL_BUTTON_MIDDLE);
        key_map["mouse_right"] = mouse_flags & SDL_BUTTON(SDL_BUTTON_RIGHT);

        mouse_coordinates.x = x;
        mouse_coordinates.y = y;
	}

};// class sdl_input_listener

