#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL_image.h>

#include <crosswind/modules/javascript/json.hpp>
#include <crosswind/interface/graphical/video.hpp>
#include <crosswind/interface/graphical/detail/sprite.hpp>
#include <crosswind/implementation/platform/exception.hpp>
#include <crosswind/implementation/graphical/object/model.hpp>
#include <crosswind/implementation/graphical/object/sprite_animation.hpp>
#include <crosswind/implementation/graphical/opengl/window.hpp>
#include <crosswind/implementation/graphical/opengl/renderer.hpp>
#include <crosswind/implementation/graphical/opengl/texture.hpp>
#include <crosswind/implementation/graphical/sdl/surface.hpp>

namespace cw{
namespace implementation{
namespace graphical{

  class video;

}// namespace graphical
}// namespace implementation
}// namespace cw

class cw::implementation::graphical::video: public cw::interface::graphical::video{
public:
	video(const std::string& title,
		  const glm::i32vec2 window_position,
		  const glm::i32vec2 window_resolution,
		  const float& fps,
		  const int& video_flags,
		  const int& window_flags,
	      const bool& resizable) {

		if ((IMG_Init(video_flags) & video_flags) != video_flags)
		  throw platform::exception("IMG_Init");


		int final_flags = window_flags;

		if(resizable){
			final_flags |= SDL_WINDOW_RESIZABLE;
		}

        window = std::make_shared<opengl::window>(title,
		                                          window_position,
		                                          window_resolution,
		                                          fps,
												  final_flags);

		renderer = std::make_shared<opengl::renderer>();
	}

	virtual ~video() {
		IMG_Quit();
	}

	void set_window_icon(const std::string& path){
		auto surface = std::make_unique<sdl::surface>(path);
		window->set_icon(surface->data.ptr());

	}

    void load_texture(const std::string& name, const std::string& path){

        if ( texture_list.find(name) == texture_list.end()) {
            auto surface = std::make_unique<sdl::surface>(path);

            texture_list[name] = std::make_shared<opengl::texture>
                    (glm::vec2(surface->data.ptr()->w, surface->data.ptr()->h),
                            surface->data.ptr()->format->BytesPerPixel,
                            surface->data.ptr()->pixels);
        }

    }

    std::shared_ptr<interface::graphical::detail::texture> load_texture(const std::string& name){
        
        return texture_list[name];
        
    }

	std::shared_ptr<interface::graphical::object::model> load_model(const glm::vec3& origin,
		                                      const glm::vec3& size, 
		                                      const std::string& template_file){

	    modules::javascript::json json;
	    json.from_file(template_file);

	    auto& raw_json = json.data;

	    auto model = std::make_shared<implementation::graphical::object::model>();

	    for (auto t = raw_json["texture"].begin_members(); t != raw_json["texture"].end_members(); ++t)
	    {
	        load_texture(t->name(), t->value().as<std::string>());
	    }

	    std::map<std::string, std::shared_ptr<interface::graphical::detail::sprite> > sprites;

	    for (auto s = raw_json["sprites"].begin_members(); s != raw_json["sprites"].end_members(); ++s)
	    {
	        std::string name    = s->name();                        // sprite name

	        auto s_props = s->value().begin_members();

	        std::string texture = s_props->name();  // mapped texture.

	        glm::vec4 uv(s_props->value()[0].as<double>(), // uv coordinates.
	                     s_props->value()[1].as<double>(),
	                     s_props->value()[2].as<double>(),
	                     s_props->value()[3].as<double>());

	        sprites[name] = std::make_shared<interface::graphical::detail::sprite>(origin,
																				   size,
																				   glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
																			       uv,
			                                                                       load_texture(texture)->id);
	    }

	    std::map<std::string, std::shared_ptr<interface::graphical::object::sprite_animation> > animations;

	    for (auto a = raw_json["animations"].begin_members(); a != raw_json["animations"].end_members(); ++a)
	    {

	        std::vector<std::shared_ptr<interface::graphical::detail::sprite> > frames;

	        for(auto f = a->value()["frames"].begin_elements(); f != a->value()["frames"].end_elements();  ++f){
	            frames.push_back(sprites[f->as<std::string>()]);
	        }

	        auto animation = std::make_shared<implementation::graphical::object::sprite_animation>();
	        animation->duration = a->value()["time"].as<double>();
	        animation->frames = frames;

	        animations[a->name()] = animation;
	    }

	    model->set_animations(animations);

	    model->change_animation(raw_json["properties"]["default-animation"].as<std::string>());

		model->get_render_sprite_list()["current"] =
				model->get_animations()["current"]->frames[model->get_animations()["current"]->current_frame];

	    model->set_origin(origin);
	    model->set_size(size);

	    return model;
	}

};// class video