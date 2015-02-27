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

    	cw::core::javascript::json json;
 		json.from_file(template_file);

        auto& raw_json = json.data.acquire();

        int texture_w   = raw_json["attributes"]["default-size"][0].as<int>();
        int texture_h   = raw_json["attributes"]["default-size"][1].as<int>();
//        int texture_d  = raw_json["attributes"]["default-size"][0].as<int>();

        for (auto t = raw_json["textures"].begin_members(); t != raw_json["textures"].end_members(); ++t)
        {
            std::string path = t->value().as<std::string>();
            auto mapping = std::shared_ptr<texture_mapping>(new texture_mapping());
            mapping->texture = std::shared_ptr<drawing::sdl_texture>(new drawing::sdl_texture(renderer, path.c_str()));
            load_texture(t->name(), mapping);
        }

        for (auto s = raw_json["sprites"].begin_members(); s != raw_json["sprites"].end_members(); ++s)
        {
            for(auto cord = s->value().begin_members(); cord != s->value().end_members(); ++cord){

                int x = cord->value()[0].as<int>();
                int y = cord->value()[1].as<int>();
                int w = cord->value()[2].as<int>();
                int h = cord->value()[3].as<int>();

                auto mapping =  std::shared_ptr<sprite_mapping>(new sprite_mapping());
                mapping->name = cord->name();
                mapping->clip = std::shared_ptr<geometry::rectangle<int> >(new geometry::rectangle<int>(x, y, w, h));
                load_sprite(s->name(), mapping);

            }

        }

		for (auto a = raw_json["animations"].begin_members(); a != raw_json["animations"].end_members(); ++a)
		{
            std::vector<std::string> frames;

			for(auto f = a->value()["frames"].begin_elements(); f != a->value()["frames"].end_elements();  ++f){
                frames.push_back(f->as<std::string>());
			}

            auto mapping = std::shared_ptr<animation_mapping>(new animation_mapping());
            mapping->duration = a->value()["time"].as<double>();
            mapping->frames = frames;

            load_animation(a->name(), mapping);
        }

        swap_animation("current", raw_json["properties"]["default-animation"].as<std::string>());
        swap_texture("current", raw_json["properties"]["default-texture"].as<std::string>());

        json.data.release();

        delta_count = 0;

	}

	void update(double delta){

        delta_count += delta;

        auto& a = animations.data.acquire();

        if(delta_count >= a["current"]->duration / a["current"]->frames.size()){

            delta_count = 0;

            a["current"]->current_frame++;

            if(a["current"]->current_frame >= a["current"]->frames.size()){
                a["current"]->current_frame = 0;
            }
        }

        swap_sprite("current", a["current"]->frames[a["current"]->current_frame]);

        animations.data.release();
    }

	void render(auto sdl_renderer){

		auto& m = textures.data.acquire();
		auto& s = sprites.data.acquire();

		sdl_renderer->copy_ex(*m["current"]->texture, bounds, s["current"]->clip.get());

		sprites.data.release();
		textures.data.release();
	}

   void load_texture(const std::string& name, std::shared_ptr<texture_mapping> new_texture){
        auto& m = textures.data.acquire();

        m[name] = new_texture;

        textures.data.release();
    }

	void swap_texture(const std::string& previous_texture, const std::string& new_texture){
		auto& m = textures.data.acquire();

		if(m[previous_texture] != m[new_texture]){
			m[previous_texture] = m[new_texture];			
		}

		textures.data.release();
	}

    void load_sprite(const std::string& name, std::shared_ptr<sprite_mapping> new_sprite){
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

    void load_animation(const std::string& name, std::shared_ptr<animation_mapping> new_animation){
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

    void load_event(const std::string& name, std::shared_ptr<event_mapping> new_event){
        auto& e = events.data.acquire();

        e[name] = new_event;

        events.data.release();
    }

    void swap_event(const std::string& previous_event, const std::string& new_event){
        auto& e = events.data.acquire();

        if(e[previous_event] != e[new_event]){
            e[previous_event] = e[new_event];
        }

        events.data.release();
    }

	geometry::rectangle<int> bounds;

private:
    float delta_count;

private:
    core::concurrent::mutexed_map<std::string, std::shared_ptr< texture_mapping   > > textures;
	core::concurrent::mutexed_map<std::string, std::shared_ptr< sprite_mapping    > > sprites;
    core::concurrent::mutexed_map<std::string, std::shared_ptr< animation_mapping > > animations;
    core::concurrent::mutexed_map<std::string, std::shared_ptr< event_mapping     > > events;

    core::functional::delegate<void> on_mouse_click;
};// class standard_actor