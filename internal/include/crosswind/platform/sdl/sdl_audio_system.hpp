#pragma once

#include <SDL2/SDL_mixer.h>

#include <crosswind/platform/sdl/sdl_exception.hpp>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_audio_system;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_audio_system{
public:
	template<typename... Args>
	sdl_audio_system(Args... args) {

		if (Mix_OpenAudio(args...) < 0)
		 throw sdl_exception("SDL_mixer could not initialize! SDL_mixer Error: %s\n");//, Mix_GetError());

	}

	~sdl_audio_system() {
    	Mix_Quit();
	}


	// non-copyable
	sdl_audio_system(const sdl_audio_system& other) = delete;
	sdl_audio_system& operator=(const sdl_audio_system& other) = delete;

	// non-movable
	sdl_audio_system(sdl_audio_system&& other) = delete;
	sdl_audio_system& operator=(sdl_audio_system&& other) = delete;

	// non-default
	sdl_audio_system() = delete;
};// class sdl_audio_system