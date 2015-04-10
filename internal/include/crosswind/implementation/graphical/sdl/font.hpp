#pragma once 

#include <SDL2/SDL_ttf.h>

#include <crosswind/modules/functional/resource_property.hpp>

namespace cw{
namespace implementation{
namespace graphical{
namespace sdl{

	class font;

}// namespace sdl
}// namespace graphical
}// namespace implementation
}// namespace cw


class cw::implementation::graphical::sdl::font{
public:
	font(const std::string& file_path, const uint32_t& size): 
	data(TTF_OpenFont, TTF_CloseFont, file_path.c_str(), size){
		// error loading font
/*		if( font == NULL )
		{
			throw exception();
		}*/
    }

	functional::resource_property<TTF_Font> data;
};// class font
