#pragma once

#include <string>
#include <map>

#include <SDL2/SDL_keyboard.h>

namespace cw{
namespace platform{
namespace input{
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

	class keyboard_listener;

}// namespace input
}// namespace platform
}// namespace cw


class cw::platform::input::keyboard_listener{
public:
	keyboard_listener(){

        int array_counter = 0;

        int32_t keymap[SDL_NUM_SCANCODES];

        SDL_GetDefaultKeymap(keymap);

        while(array_counter < SDL_NUM_SCANCODES){

            std::string key_name = SDL_GetKeyName(keymap[array_counter]);
              if(!key_name.empty())
                  key_map[key_name] = false;

            array_counter++;
        }

	}

	bool is_key_down(const std::string& key){

		return key_map[key];

	}

	void refresh(){

		const uint8_t* state = SDL_GetKeyboardState(NULL);

		for(auto& key : key_map){
			key_map[key.first] = state[SDL_GetScancodeFromName(key.first.c_str())];
		}


	}

    std::map<std::string, bool> key_map;

};// class keyboard_listener

