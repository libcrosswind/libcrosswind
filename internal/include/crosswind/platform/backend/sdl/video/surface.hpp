#pragma once 

#include <SDL2/SDL_image.h>

#include <crosswind/concurrent/resource_property.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace sdl{
namespace video{

	class surface;

}// namespace video
}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw


class cw::platform::backend::sdl::video::surface{
public:
	surface(const std::string& file_path): data(IMG_Load, SDL_FreeSurface, file_path.c_str()){

    }

	concurrent::resource_property<SDL_Surface> data;
};// class surface
