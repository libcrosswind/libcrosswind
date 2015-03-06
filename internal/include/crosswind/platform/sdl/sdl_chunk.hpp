#pragma once

#include <SDL2/SDL_mixer.h>
#include <crosswind/concurrent/resource_property.hpp>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_chunk;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_chunk{
public:
	sdl_chunk(const std::string& file_path):
            music(Mix_LoadWAV_RW, Mix_FreeChunk, SDL_RWFromFile(file_path.c_str(), "rb"), 1) {

	}

	concurrent::resource_property<Mix_Chunk> music;
	
};// class sdl_chunk