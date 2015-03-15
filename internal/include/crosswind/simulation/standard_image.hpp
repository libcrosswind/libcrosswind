#pragma once

#include <crosswind/javascript/json.hpp>
#include <crosswind/math/vector3.hpp>
#include <crosswind/platform/sdl/sdl_renderer.hpp>
#include <crosswind/platform/sdl/sdl_texture.hpp>
#include <crosswind/simulation/detail/object.hpp>
#include <crosswind/simulation/detail/standard_actor.hpp>
#include <crosswind/simulation/detail/graphical_actor.hpp>

namespace cw{
namespace simulation{

	class standard_image;

}// namespace simulation
}// namespace cw


class cw::simulation::standard_image: public cw::simulation::detail::object,
                                      public cw::simulation::detail::standard_actor,
                                      public cw::simulation::detail::graphical_actor{
public:
	standard_image( const math::vector3& p,
                    const math::vector3& s): object(p, s){

	}

    virtual void init(const std::shared_ptr<platform::sdl::sdl_renderer> sdl_renderer,
            const std::string& template_file){

//            load_image(sdl_renderer, template_file);

    }

	virtual void update(double delta){


    }

	virtual void render(std::shared_ptr<platform::sdl::sdl_gl_renderer> sdl_gl_renderer){
/*
		auto& m = textures.data.acquire();
		auto& s = sprites.data.acquire();

		sdl_renderer->copy_ex(m["current"]->texture, bounds, s["current"]->clip.get());

		sprites.data.release();
		textures.data.release();*/
	}

protected:
    virtual void load_image(  const std::shared_ptr<platform::sdl::sdl_renderer> sdl_renderer,
            const std::string& template_file){
/*
        cw::javascript::json json;
        json.from_file(template_file);

        auto& raw_json = json.data.acquire();

        for (auto t = raw_json["textures"].begin_members(); t != raw_json["textures"].end_members(); ++t)
        {
            std::string path = t->value().as<std::string>();
            auto mapping = std::make_shared<detail::texture_mapping>();
            auto renderer_ptr = sdl_renderer->renderer.acquire();

            mapping->texture = std::make_shared<platform::sdl::sdl_texture>(renderer_ptr, path.c_str());

            sdl_renderer->renderer.release();
            store_graphical_item(textures, t->name(), mapping);
        }

        for (auto s = raw_json["sprites"].begin_members(); s != raw_json["sprites"].end_members(); ++s)
        {
            for(auto cord = s->value().begin_members(); cord != s->value().end_members(); ++cord){

                int x = cord->value()[0].as<int>();
                int y = cord->value()[1].as<int>();
                int w = cord->value()[2].as<int>();
                int h = cord->value()[3].as<int>();

                auto mapping =  std::make_shared<detail::sprite_mapping>();
                mapping->name = cord->name();
                mapping->clip = std::make_shared<geometry::rectangle<int> >(x, y, w, h);
                store_graphical_item(sprites, s->name(), mapping);

            }

        }

        for (auto a = raw_json["animations"].begin_members(); a != raw_json["animations"].end_members(); ++a)
        {
            std::vector<std::string> frames;

            for(auto f = a->value()["frames"].begin_elements(); f != a->value()["frames"].end_elements();  ++f){
                frames.push_back(f->as<std::string>());
            }

            auto mapping = std::make_shared<detail::animation_mapping>();
            mapping->duration = a->value()["time"].as<double>();
            mapping->frames = frames;

            store_graphical_item(animations, a->name(), mapping);
        }

        swap_graphical_item(animations, "current", raw_json["properties"]["default-animation"].as<std::string>());
        swap_graphical_item(textures,   "current", raw_json["properties"]["default-texture"].as<std::string>());

        json.data.release();*/
    }


};