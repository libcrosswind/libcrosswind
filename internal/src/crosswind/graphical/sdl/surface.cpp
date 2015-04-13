#include "crosswind/graphical/sdl/surface.hpp"

cw::graphical::sdl::surface::surface(const std::string& file_path):
data(IMG_Load, 
	 SDL_FreeSurface, 
	 file_path.c_str()){

}

cw::graphical::sdl::surface::surface(TTF_Font* font,
									 const std::string& text,
									 const SDL_Color& color):
data(TTF_RenderText_Blended, 
	 SDL_FreeSurface, 
	 font, 
	 text.c_str(), 
	 color){

}