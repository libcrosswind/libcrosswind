#pragma once 

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

	//Use this if you know what are you doing. This constructor is for other surface allocations
	surface(TTF_Font* font, const std::string& text, const SDL_Color& color):
			data(TTF_RenderText_Blended, SDL_FreeSurface, font, text.c_str(), color){

	}

	functional::resource_property<SDL_Surface> data;
};// class surface
