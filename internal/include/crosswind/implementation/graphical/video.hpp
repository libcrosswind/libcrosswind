#pragma once

#include <memory>
#include <string>
#include <cstdint>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <crosswind/modules/javascript/json.hpp>
#include <crosswind/interface/graphical/video.hpp>
#include <crosswind/interface/graphical/object/text.hpp>
#include <crosswind/interface/graphical/detail/sprite.hpp>

#include <crosswind/implementation/platform/exception.hpp>
#include <crosswind/implementation/graphical/object/model.hpp>
#include <crosswind/implementation/graphical/object/sprite_animation.hpp>
#include <crosswind/implementation/graphical/opengl/window.hpp>
#include <crosswind/implementation/graphical/opengl/renderer.hpp>
#include <crosswind/implementation/graphical/opengl/texture.hpp>

#include <crosswind/implementation/graphical/sdl/font.hpp>
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
		  const glm::i32vec2& window_position,
		  const glm::i32vec2& window_resolution,
		  const float& fps,
		  const int& video_flags,
		  const int& window_flags,
	      const bool& resizable) {

		if ((IMG_Init(video_flags) & video_flags) != video_flags)
		  throw platform::exception("IMG_Init");

		if (TTF_Init() == -1 )
			throw platform::exception("TTF_Init");

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
		TTF_Quit();
	}

	void set_window_icon(const std::string& path){
		auto surface = std::make_unique<sdl::surface>(path);
		window->set_icon(surface->data.ptr());
	}

    void load_texture(const std::string& name, const std::string& path){

        if (texture_map.find(name) == texture_map.end()) {
            auto surface = std::make_unique<sdl::surface>(path);

			texture_map[name] = std::make_shared<opengl::texture>
                    (glm::vec2(surface->data.ptr()->w, surface->data.ptr()->h),
                            surface->data.ptr()->format->BytesPerPixel,
                            surface->data.ptr()->pixels);
        }

    }

    std::shared_ptr<interface::graphical::detail::texture> load_texture(const std::string& name){
        
        return texture_map[name];
        
    }

	std::shared_ptr<sdl::font> load_font(const std::string& font_path, const uint32_t& size){

		std::shared_ptr<sdl::font> font;

		std::string font_name =
				font_path.substr(font_path.size() - 4, font_path.size()) + "_" + std::to_string(size);

		if(font_map.find(font_name) == font_map.end()){
			font_map[font_name] = std::make_shared<class sdl::font>(font_path, size);
			font = font_map[font_name];
		} else {
			font = font_map[font_name];
		}

		return font;
	}

	void remove_texture(const std::string& texture_name){
		if(texture_map.find(texture_name) != texture_map.end()){
			texture_map[texture_name] = nullptr;
		} else {
			// throw
		}
	}

	void load_text(std::shared_ptr<interface::graphical::object::text> text, const std::string& font_path){

		auto font    = load_font(font_path, text->get_size());

		auto surface = text->render(font);

		if (texture_map.find(text->get_name()) == texture_map.end()) {

			texture_map[text->get_name()] = std::make_shared<opengl::texture>(glm::vec2(surface->data.ptr()->w,
																						surface->data.ptr()->h),
																			  surface->data.ptr()->format->BytesPerPixel,
																			  surface->data.ptr()->pixels);

		} else {
			remove_texture(text->get_name());

			texture_map[text->get_name()] = std::make_shared<opengl::texture>(glm::vec2(surface->data.ptr()->w,
																						surface->data.ptr()->h),
																			  surface->data.ptr()->format->BytesPerPixel,
																			  surface->data.ptr()->pixels);
		}


		auto text_size = glm::vec3(surface->data.ptr()->w, surface->data.ptr()->h, 0.0f);

		auto uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

		auto render_sprite = std::make_shared<interface::graphical::detail::sprite>(text->get_origin(),
												 								    text_size,
															  						text->get_color(),
															   						uv,
															   						load_texture(text->get_name())->id);


		text->set_render_sprite(render_sprite);
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

		model->set_render_sprite(model->get_animations()["current"]->
				                 frames[model->get_animations()["current"]->current_frame]);

	    model->set_origin(origin);
	    model->set_size(size);

	    return model;
	}

private:
	std::map<std::string, std::shared_ptr<sdl::font> > font_map;


};// class video