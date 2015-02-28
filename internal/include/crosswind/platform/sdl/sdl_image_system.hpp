#pragma once

#include <SDL2/SDL_image.h>

#include <crosswind/platform/sdl/sdl_exception.hpp>

namespace cw{
namespace platform{
namespace sdl{

  class sdl_image_system;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_image_system{
public:
	sdl_image_system(int flags) {
		if ((IMG_Init(flags) & flags) != flags)
		  throw sdl_exception("IMG_Init");
	}

	// non-copyable
	sdl_image_system(const sdl_image_system& other) = delete;
	sdl_image_system& operator=(const sdl_image_system& other) = delete;

	// non-movable
	sdl_image_system(sdl_image_system&& other) = delete;
	sdl_image_system& operator=(sdl_image_system&& other) = delete;

	~sdl_image_system() {
		IMG_Quit();
	}

	int init_more(int flags) {
	int ret;
		if (((ret = IMG_Init(flags)) & flags) != flags)
		  throw sdl_exception("IMG_Init");
		return ret;
	}

	int init_flags() {
		return IMG_Init(0);
	}

};
 