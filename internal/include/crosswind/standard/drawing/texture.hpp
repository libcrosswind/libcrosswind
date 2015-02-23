#pragma once 

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

namespace cw{
namespace standard{
namespace drawing{

	class sdl_texture;

}// namespace drawing
}// namespace standard
}// namespace cw


class cw::standard::drawing::sdl_texture{
public:
	core::concurrent::resource_property<SDL_Texture> texture;

	template<typename... Args>
	sdl_texture(Args... args): texture(IMG_LoadTexture, SDL_DestroyTexture, args...){
		
	}

/*	point get_size() const {
		int w, h;
		if (SDL_QueryTexture(texture_, nullptr, nullptr, &w, &h) != 0)
			throw sdl_exception("SDL_QueryTexture");
		return point(w, h);
	}*/

};

