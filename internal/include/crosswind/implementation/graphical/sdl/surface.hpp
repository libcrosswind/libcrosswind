#pragma once 

#include <SDL2/SDL_image.h>

#include <crosswind/modules/functional/resource_property.hpp>

namespace cw{
namespace implementation{
namespace graphical{
namespace sdl{

	class surface;

}// namespace sdl
}// namespace graphical
}// namespace implementation
}// namespace cw


class cw::implementation::graphical::sdl::surface{
public:
	surface(const std::string& file_path): data(IMG_Load, SDL_FreeSurface, file_path.c_str()){

    }

	functional::resource_property<SDL_Surface> data;
};// class surface
