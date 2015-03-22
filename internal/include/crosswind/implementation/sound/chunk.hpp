#pragma once

#include <SDL2/SDL_mixer.h>
#include <crosswind/modules/functional/resource_property.hpp>

namespace cw{
namespace implementation{
namespace sound{

	class chunk;

}// namespace sound
}// namespace implementation
}// namespace cw

class cw::implementation::sound::chunk{
public:
	chunk(const std::string& file_path):
            data(Mix_LoadWAV_RW, Mix_FreeChunk, SDL_RWFromFile(file_path.c_str(), "rb"), 1) {
	}

	functional::resource_property<Mix_Chunk> data;
};// class chunk