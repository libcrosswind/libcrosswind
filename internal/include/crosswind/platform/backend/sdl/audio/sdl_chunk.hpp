#pragma once

#include <SDL2/SDL_mixer.h>
#include <crosswind/concurrent/resource_property.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace sdl{
namespace audio{

	class chunk;

}// namespace audio
}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::sdl::audio::chunk : public cw::platform::backend::audio::chunk_interface{
public:
	chunk(const std::string& file_path):
            data(Mix_LoadWAV_RW, Mix_FreeChunk, SDL_RWFromFile(file_path.c_str(), "rb"), 1) {
	}

	concurrent::resource_property<Mix_Chunk> data;
};// class chunk