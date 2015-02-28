#pragma once

#include <crosswind/core/javascript/json.hpp>
#include <crosswind/platform/sdl/sdl_renderer.hpp>
#include <crosswind/standard/drawing/texture.hpp>

namespace cw{
namespace simulation{

	class standard_image;

}// namespace simulation
}// namespace cw


class cw::simulation::standard_image: public cw::simulation::detail::object,
                                      public cw::simulation::detail::standard_actor,
                                      public cw::simulation::detail::graphical_actor{
public:
	standard_image( const geometry::point<int>& position,
                    const geometry::point<int>& size, 
                    const auto& renderer,
                    const std::string& template_file): object(position, size){

		cw::core::javascript::json json;
 		json.from_file(template_file);

        auto& raw_json = json.data.acquire();

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

	}

	virtual void update(double delta){

        delta_count += delta;

        auto& a = animations.data.acquire();

        if(delta_count >= a["current"]->duration / a["current"]->frames.size()){

            delta_count = 0;

            a["current"]->current_frame++;

            if(a["current"]->current_frame >= a["current"]->frames.size()){
                a["current"]->current_frame = 0;
            }
        }

        sprites.swap("current", a["current"]->frames[a["current"]->current_frame]);

        animations.data.release();
    }


	virtual void render(auto sdl_renderer){

		auto& m = textures.data.acquire();
		auto& s = sprites.data.acquire();

		sdl_renderer->copy_ex(m["current"]->texture, bounds, s["current"]->clip.get());

		sprites.data.release();
		textures.data.release();
	}

private:
    core::container::cacheable<std::string, std::shared_ptr< texture_mapping   > > textures;
    core::container::cacheable<std::string, std::shared_ptr< sprite_mapping    > > sprites;
    core::container::cacheable<std::string, std::shared_ptr< animation_mapping > > animations;
};