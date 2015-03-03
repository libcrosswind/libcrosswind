#pragma once

#include <SDL_mixer.h>
#include <crosswind/concurrent/resource_property.hpp>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_music;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_chunk{
public:
	sdl_music(const std::string& filepath): music(Mix_LoadWAV, Mix_FreeChunk, filepath.c_str()) {

	}



	concurrent::resource_property<Mix_Chunk> music;
};
