#pragma once 

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#include <crosswind/concurrent/resource_property.hpp>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_texture;

}// namespace sdl
}// namespace platform
}// namespace cw


class cw::platform::sdl::sdl_texture{
public:
	template<typename... Args>
	sdl_texture(Args... args): data(IMG_LoadTexture, SDL_DestroyTexture, args...){
		
	}

	concurrent::resource_property<SDL_Texture> data;
};// class sdl_texture
