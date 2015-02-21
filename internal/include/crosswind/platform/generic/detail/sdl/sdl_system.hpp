#pragma once

#include <SDL2/SDL.h>
#include <crosswind/platform/generic/detail/sdl/sdl_exception.hpp>

namespace cw{
namespace platform{
namespace generic{
namespace detail{
namespace sdl{

	class sdl_system;

}// namespace sdl
}// namespace detail
}// namespace generic
}// namespace platform
}// namespace cw


class cw::platform::generic::detail::sdl::sdl_system{
public:
	sdl_system(auto flags) {
		if (SDL_Init(flags) != 0)
			throw sdl_exception("SDL_Init");
	}

	~sdl_system() {
		SDL_Quit();
	}

	auto was_init(auto flags) {
		return SDL_WasInit(flags);
	}

	void init_subsistem(auto flags) {
		if (SDL_InitSubSystem(flags) != 0)
			throw sdl_exception("SDL_InitSubsystem");
	}

	void quit_subsystem(auto flags) {
		SDL_QuitSubSystem(flags);
	}

};// class sdl