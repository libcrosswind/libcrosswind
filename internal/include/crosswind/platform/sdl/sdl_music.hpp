#pragma once

#include <SDL2/SDL_mixer.h>
#include <crosswind/concurrent/resource_property.hpp>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_music;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_music{
public:
	sdl_music(const std::string& filepath): music(Mix_LoadMUS, Mix_FreeMusic, filepath.c_str()) {

	}

	concurrent::resource_property<Mix_Music> music;
};// class sdl_music
