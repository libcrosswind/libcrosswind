#pragma once 

#include <SDL2/SDL_image.h>

#include <crosswind/concurrent/resource_property.hpp>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_surface;

}// namespace sdl
}// namespace platform
}// namespace cw


class cw::platform::sdl::sdl_surface{
public:
	sdl_surface(const std::string& file_path): data(IMG_Load, SDL_FreeSurface, file_path.c_str()){

    }

	concurrent::resource_property<SDL_Surface> data;
	
};// class sdl_surface
