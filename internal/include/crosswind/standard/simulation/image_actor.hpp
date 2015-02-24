#pragma once

#include <SDL2/SDL_events.h>

#include <crosswind/standard/drawing/texture.hpp>
#include <crosswind/standard/geometry/point.hpp>
#include <crosswind/standard/geometry/rectangle.hpp>


namespace cw{
namespace standard{
namespace simulation{

	class image_actor;

}// namespace simulation
}// namespace standard
}// namespace cw

class cw::standard::simulation::image_actor{
public:

	image_actor(const geometry::point<int> position, std::string template_file): 
	bounds(0, 0, 0, 0){

	}

	void handle_event(SDL_Event* e){

		//If mouse event happened
		if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );

			if(bounds.contains_xy(x, y)){ //Mouse is inside button
				//Set mouse over sprite
				switch(e->type)
				{
					case SDL_MOUSEMOTION:
						swap_texture("current", "mouse_over");
					break;
				
					case SDL_MOUSEBUTTONDOWN:
						swap_texture("current", "mouse_down");
					break;
					
					case SDL_MOUSEBUTTONUP:
						swap_texture("current", "mouse_up");
					break;
				}
			} else {//Mouse is outside button
				swap_texture("current", "mouse_out");			
			}

		}
	}

	void update(double delta){
		
	}

	void render(auto sdl_renderer){
		
		auto& m = textures.data.acquire();

		sdl_renderer->copy_ex(*m["current"], bounds);

		textures.data.release();
	}

	void swap_texture(const std::string previous_texture, const std::string new_texture){
		auto& m = textures.data.acquire();

		if(m[previous_texture] != m[new_texture]){
			m[previous_texture] = m[new_texture];			
		}

		textures.data.release();
	}

	geometry::rectangle<int> bounds;
	core::concurrent::mutexed_map<std::string, std::shared_ptr<drawing::sdl_texture> > textures;
};// class image_actor