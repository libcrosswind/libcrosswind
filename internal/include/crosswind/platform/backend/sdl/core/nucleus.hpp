#pragma once

#include <SDL2/SDL.h>

#include <crosswind/platform/backend/sdl/core/exception.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace sdl{
namespace core{

	class nucleus;

}// namespace core
}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::sdl::core::nucleus{
public:
	nucleus(auto flags) {
		if (SDL_Init(flags) != 0)
			throw exception("SDL_Init");
	}

	~nucleus() {
		SDL_Quit();
	}

	auto was_init(auto flags) {
		return SDL_WasInit(flags);
	}

	void init_subsystem(auto flags) {
		if (SDL_InitSubSystem(flags) != 0)
			throw exception("SDL_InitSubsystem");
	}

	void quit_subsystem(auto flags) {
		SDL_QuitSubSystem(flags);
	}

};// class nucleus 