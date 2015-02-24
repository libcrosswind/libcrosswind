#pragma once

namespace cw{
namespace standard{
namespace simulation{

	class image_actor;

}// namespace simulation
}// namespace standard
}// namespace cw

class cw::standard::simulation::image_actor{
public:

	image_actor(const drawing::point<int> position, std::string template_file){

	}

	void handle_event(SDL_Event* e){

		//If mouse event happened
		if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );

			auto& rect = bounds.acquire();

			rect.contains(x, y) ? //Mouse is inside button
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
			://Mouse is outside button
				swap_texture("current", "mouse_out");			

			bounds.release();
		}
	}

	void update(double delta){
		
	}

	void render(auto sdl_renderer){
		auto& rect = bounds.acquire();

		auto& m = textures.acquire();

		sdl_renderer->copy_ex(m["current"], rect);

		textures.release();
		bounds.release();
	}

	void swap_texture(const std::string previous_texture, const std::string new_texture){
		auto& m = textures.acquire();

		if(&m[previous_texture] != &m[new_texture]){
			m[previous_texture] = m[new_texture];			
		}

		textures.release();
	}

	core::concurrent::mutexed_property<geometry::rectangle<int> > bounds;
	core::concurrent::mutexed_container<std::map<std::string, drawing::texture> > textures;
};// class image_actor