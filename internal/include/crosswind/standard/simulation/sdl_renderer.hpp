#pragma once

#include <vector>
#include <SDL2/SDL_render.h>

#include <crosswind/core/concurrent/resource_property.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_exception.hpp>
#include <crosswind/standard/drawing/texture.hpp>

namespace cw{
namespace standard{
namespace simulation{

	class sdl_renderer;

}// namespace simulation
}// namespace standard
}// namespace cw


class cw::standard::simulation::sdl_renderer{
public:
	core::concurrent::resource_property<SDL_Renderer> renderer;

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
			throw cw::platform::generic::detail::sdl::sdl_exception("SDL_RenderClear");

		renderer.release();
	}

 	void set_draw_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) {
 		auto renderer_ptr = renderer.acquire();

		if (SDL_SetRenderDrawColor(renderer_ptr, r, g, b, a) != 0)
			throw cw::platform::generic::detail::sdl::sdl_exception("SDL_SetRenderDrawColor");

		renderer.release();
	}

	void copy(drawing::sdl_texture& sdl_texture) {
 		auto renderer_ptr = renderer.acquire();
		auto texture_ptr = sdl_texture.texture.acquire();

		if (SDL_RenderCopy(renderer_ptr, texture_ptr, nullptr, nullptr) != 0)
			throw cw::platform::generic::detail::sdl::sdl_exception("SDL_RenderCopy");

		sdl_texture.texture.release();
		renderer.release();
	}

	template<typename T>
	void copy_ex(drawing::sdl_texture& sdl_texture, 
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

			render_quad.w = c_dim.x;
			render_quad.h = c_dim.y;

			clip->size.release();
			clip->position.release();

			render_clip_ptr = &render_clip;
		}

		auto renderer_ptr = renderer.acquire();
		auto texture_ptr = sdl_texture.texture.acquire();

		//Render to screen
		if (SDL_RenderCopyEx(renderer_ptr, texture_ptr, render_clip_ptr, &render_quad, angle, center, flip) != 0)
			throw cw::platform::generic::detail::sdl::sdl_exception("SDL_RenderCopy");

		sdl_texture.texture.release();
		renderer.release();
	}


};// class sdl_renderer