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
    typedef std::shared_ptr<drawing::sdl_texture> texture;
    typedef std::pair<std::string, std::shared_ptr<geometry::rectangle<int> > > sprite;
    typedef std::pair<int, std::vector<std::string> > animation;
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

        for (auto t = raw_json["textures"].begin_members(); t != raw_json["textures"].end_members(); ++t)
        {
            std::string path = t->value().as<std::string>();
            texture tex(new drawing::sdl_texture(renderer, path.c_str()));
            load_texture(t->name(), tex);
        }

        for (auto s = raw_json["sprites"].begin_members(); s != raw_json["sprites"].end_members(); ++s)
        {
            for(auto cord = s->value().begin_members(); cord != s->value().end_members(); ++cord){

                int nx = cord->value()[0].as<int>();
                int ny = cord->value()[1].as<int>();
                int nw = cord->value()[2].as<int>();
                int nh = cord->value()[3].as<int>();

                std::shared_ptr<geometry::rectangle<int> > rect(new geometry::rectangle<int>(nx, ny, nw, nh));

                load_sprite(s->name(), sprite(cord->name(), rect));

            }

        }

		for (auto a = raw_json["animations"].begin_members(); a != raw_json["animations"].end_members(); ++a)
		{
            std::vector<std::string> frames;

			for(auto f = a->value()["frames"].begin_elements(); f != a->value()["frames"].end_elements();  ++f){

                frames.push_back(f->as<std::string>());
			}


            load_animation(a->name(), animation(a->value()["time"].as<int>(), frames));
        }

        for (auto e = raw_json["events"].begin_members(); e != raw_json["events"].end_members(); ++e)
        {
            std::cout << e->name() << std::endl;
            for(auto p = e->value().begin_members(); p != e->value().end_members();  ++p){

                std::cout << p->name() << " " << p->value() << std::endl;

            }
        }

        json.data.release();

        //swap_texture("current", "mouse_up");
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
		auto& s = sprites.data.acquire();

		sdl_renderer->copy_ex(*m["current"], bounds, s["current"].second.get());

		sprites.data.release();
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

    void load_sprite(const std::string& name, sprite new_sprite){
        auto& s = sprites.data.acquire();

        s[name] = new_sprite;

        sprites.data.release();
    }

    void swap_sprite(const std::string& previous_sprite, const std::string& new_sprite){
        auto& s = sprites.data.acquire();

        if(s[previous_sprite] != s[new_sprite]){
            s[previous_sprite] = s[new_sprite];
        }

        sprites.data.release();
    }

    void load_animation(const std::string& name, animation new_animation){
        auto& a = animations.data.acquire();

        a[name] = new_animation;

        animations.data.release();
    }

    void swap_animation(const std::string& previous_animation, const std::string& new_animation){
        auto& a = animations.data.acquire();

        if(a[previous_animation] != a[new_animation]){
            a[previous_animation] = a[new_animation];
        }

        animations.data.release();
    }

	geometry::rectangle<int> bounds;

private:
    core::concurrent::mutexed_map<std::string, std::shared_ptr<drawing::sdl_texture> > textures;
	core::concurrent::mutexed_map<std::string, sprite > sprites;
    core::concurrent::mutexed_map<std::string, animation > animations;

};// class image_actor