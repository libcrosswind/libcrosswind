#pragma once

#include <SDL2/SDL_events.h>

#include <crosswind/core/javascript/json.hpp>
#include <crosswind/standard/drawing/texture.hpp>
#include <crosswind/standard/geometry/point.hpp>
#include <crosswind/standard/geometry/rectangle.hpp>
#include <crosswind/standard/simulation/sdl_renderer.hpp>

namespace cw{
namespace standard{
namespace simulation{

	class image_actor;

}// namespace simulation
}// namespace standard
}// namespace cw

class cw::standard::simulation::image_actor{
public:

	image_actor(const geometry::point<int>& position,
				const geometry::point<int>& size,
				const std::string& template_file,
				auto renderer):
	bounds(position.x, position.y, size.x, size.y){

        std::cout<< template_file <<std ::endl;
    	cw::core::javascript::json json;
 		json.from_file(template_file);

        auto& raw_json = json.data.acquire();

        std::string paths[4] = {
                raw_json["textures"]["mouse_up"].as<std::string>(),
                raw_json["textures"]["mouse_down"].as<std::string>(),
                raw_json["textures"]["mouse_over"].as<std::string>(),
                raw_json["textures"]["mouse_out"].as<std::string>()
        };

        load_texture("mouse_up", std::shared_ptr<drawing::sdl_texture>(new drawing::sdl_texture(renderer, paths[0].c_str())));
        load_texture("mouse_down",std::shared_ptr<drawing::sdl_texture>(new drawing::sdl_texture(renderer, paths[1].c_str())));
        load_texture("mouse_over",std::shared_ptr<drawing::sdl_texture>(new drawing::sdl_texture(renderer, paths[2].c_str())));
        load_texture("mouse_out", std::shared_ptr<drawing::sdl_texture>(new drawing::sdl_texture(renderer, paths[3].c_str())));

        json.data.release();

        swap_texture("current", "mouse_up");
	}

	void handle_event(SDL_Event* e){

		//If mouse event happened
		if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );

			if(bounds.contains_xy(x, y)){ //Mouse is inside button
				//Set mouse over sprite
				switch(e->type){

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

    void load_texture(const std::string& name, std::shared_ptr<drawing::sdl_texture> texture){
        auto& m = textures.data.acquire();

        m[name] = texture;

        textures.data.release();
    }

	void swap_texture(const std::string& previous_texture, const std::string& new_texture){
		auto& m = textures.data.acquire();

		if(m[previous_texture] != m[new_texture]){
			m[previous_texture] = m[new_texture];			
		}

		textures.data.release();
	}

	geometry::rectangle<int> bounds;
	core::concurrent::mutexed_map<std::string, std::shared_ptr<drawing::sdl_texture> > textures;
};// class image_actor