#pragma once

#include <SDL2/SDL.h>

#include <crosswind/platform/sdl/sdl_exception.hpp>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_core_system;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_core_system{
public:
	sdl_core_system(auto flags) {
		if (SDL_Init(flags) != 0)
			throw sdl_exception("SDL_Init");
	}

	~sdl_core_system() {
		SDL_Quit();
	}

	auto was_init(auto flags) {
		return SDL_WasInit(flags);
	}

	void init_subsystem(auto flags) {
		if (SDL_InitSubSystem(flags) != 0)
			throw sdl_exception("SDL_InitSubsystem");
	}

	void quit_subsystem(auto flags) {
		SDL_QuitSubSystem(flags);
	}

};// class sdl_core_system 