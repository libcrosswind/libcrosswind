#pragma once 

#include <string>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "crosswind/modules/functional/resource_property.hpp"

// verify TTF_Font forward declaration
// verify SDL_Surface forward declaration

namespace cw{
namespace graphical{
namespace sdl{

class surface{
public:
	surface(const std::string& file_path);

	//Use this if you know what are you doing. This constructor is for other surface allocations
	surface(TTF_Font* font, const std::string& text, const SDL_Color& color);

	functional::resource_property<SDL_Surface> data;

};// class surface

}// namespace sdl
}// namespace graphical
}// namespace cw