#pragma once

#include <memory>
#include <vector>

#include <SDL2/SDL_render.h>

#include <crosswind/concurrent/resource_property.hpp>
#include <crosswind/geometry/rectangle.hpp>
#include <crosswind/platform/sdl/sdl_exception.hpp>
#include <crosswind/platform/sdl/sdl_texture.hpp>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_renderer;

}// namespace sdl
}// namespace platform
}// namespace cw


class cw::platform::sdl::sdl_renderer{
public:
	template<typename... Args>
	sdl_renderer(Args... args): renderer(SDL_CreateRenderer, SDL_DestroyRenderer, args...){
		
	}

	void present() {
		auto renderer_ptr = renderer.acquire();

		SDL_RenderPresent(renderer_ptr);

		renderer.release();
	}

	void clear() {
		auto renderer_ptr = renderer.acquire();

		if (SDL_RenderClear(renderer_ptr) != 0)
			throw sdl_exception("SDL_RenderClear");

		renderer.release();
	}

 	void set_draw_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) {
 		auto renderer_ptr = renderer.acquire();

		if (SDL_SetRenderDrawColor(renderer_ptr, r, g, b, a) != 0)
			throw sdl_exception("SDL_SetRenderDrawColor");

		renderer.release();
	}

	void copy(std::shared_ptr<sdl_texture> texture) {
 		auto renderer_ptr = renderer.acquire();
		auto texture_ptr = texture->data.acquire();

		if (SDL_RenderCopy(renderer_ptr, texture_ptr, nullptr, nullptr) != 0)
			throw sdl_exception("SDL_RenderCopy");

		texture->data.release();
		renderer.release();
	}

	template<typename T>
	void copy_ex(std::shared_ptr<sdl_texture> texture, 
				 geometry::rectangle<T>& quad, geometry::rectangle<T>* clip = nullptr,
				 double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE ){
		//Set rendering space and render to screen
		auto& q_pos = quad.position.acquire();
		auto& q_dim = quad.size.acquire();

		SDL_Rect render_quad = { q_pos.x, q_pos.y, q_dim.x, q_dim.y };


		quad.size.release();
		quad.position.release();

		SDL_Rect render_clip = { 0, 0, 0, 0};
		SDL_Rect* render_clip_ptr = nullptr;

		//Set clip rendering dimensions
		if(clip)
		{
			auto& c_pos = clip->position.acquire();
			auto& c_dim = clip->size.acquire();

			render_clip = { c_pos.x, c_pos.y, c_dim.x, c_dim.y };

			clip->size.release();
			clip->position.release();

			render_clip_ptr = &render_clip;
		}

		auto renderer_ptr = renderer.acquire();
		auto texture_ptr = texture->data.acquire();

		//Render to screen
		if (SDL_RenderCopyEx(renderer_ptr, texture_ptr, render_clip_ptr, &render_quad, angle, center, flip) != 0)
			throw sdl_exception("SDL_RenderCopy");

		texture->data.release();
		renderer.release();
	}

	concurrent::resource_property<SDL_Renderer> renderer;
};// class sdl_renderer