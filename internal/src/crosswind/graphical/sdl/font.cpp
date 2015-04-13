#include "crosswind/graphical/sdl/font.hpp"

cw::graphical::sdl::font::font(const std::string& file_path, const uint32_t& size):
data(TTF_OpenFont, TTF_CloseFont, file_path.c_str(), size){
	
		// error loading font
/*		if( font == NULL )
		{
			throw exception();
		}*/

}