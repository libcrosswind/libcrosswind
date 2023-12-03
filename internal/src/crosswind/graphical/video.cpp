#include <SDL_image.h>
#include <SDL_ttf.h>

#include "crosswind/graphical/video.hpp"
#include "crosswind/graphical/opengl/window.hpp"
#include "crosswind/graphical/opengl/renderer.hpp"
#include "crosswind/graphical/opengl/texture.hpp"
#include "crosswind/graphical/sdl/surface.hpp"
#include "crosswind/graphical/sdl/font.hpp"
#include "crosswind/graphical/object/text.hpp"
#include "crosswind/graphical/object/sprite.hpp"
#include "crosswind/graphical/object/sprite_animation.hpp"
#include "crosswind/platform/exception.hpp"

#include "crosswind/modules/javascript/json.hpp"

#include "crosswind/graphical/object/model.hpp"

// remove platform/exception

cw::graphical::video::video(const std::string& title,
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

cw::graphical::video::~video() {
	IMG_Quit();
	TTF_Quit();
}

void cw::graphical::video::set_window_icon(const std::string& path){

	auto surface = std::make_unique<sdl::surface>(path);
	window->set_icon(surface->data.ptr());

}

std::shared_ptr< cw::graphical::opengl::texture > cw::graphical::video::load_texture(const std::string& name, const std::string& path){


	try {

		if (texture_map.find(name) == texture_map.end()) {
			auto surface = std::make_unique<sdl::surface>(path);

			texture_map[name] = std::make_shared<opengl::texture>
				(glm::vec2(surface->data.ptr()->w, surface->data.ptr()->h),
					surface->data.ptr()->format->BytesPerPixel,
					surface->data.ptr()->pixels);
			return texture_map[name];
		}
	}
	catch (std::exception& ex) {
		auto err = SDL_GetError();
		std::cout << ex.what() << std::endl;
	}



}

std::shared_ptr< cw::graphical::opengl::texture > cw::graphical::video::load_texture(const std::string& name){

    return texture_map[name];

}

auto cw::graphical::video::load_font(const std::string& font_path, const uint32_t& size){

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

void cw::graphical::video::remove_texture(const std::string& texture_name){

	if(texture_map.find(texture_name) != texture_map.end()){
		texture_map[texture_name] = nullptr;
	} else {
		// throw
	}

}

std::shared_ptr
<cw::graphical::object::sprite> 
cw::graphical::video::load_sprite(const std::string& texture_name, 
								  const glm::vec3& size,
								  const glm::vec4& uv) {
	
	return std::make_shared<graphical::object::sprite>(glm::vec3(0, 0, 0),
		size,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		uv,
		load_texture(texture_name)->id);
}

std::shared_ptr<cw::graphical::object::text> cw::graphical::video::load_text(const std::string& text_name,
																			 const std::string& text_value,
																			 const glm::vec3& origin,
																			 const glm::vec3& color,
																			 const uint32_t& size,
																			 const std::string& font_path){

	auto text = std::make_shared<object::text>(text_value, origin, color);

	auto font    = load_font(font_path, size);

	auto surface = text->render(font);

	if (texture_map.find(text_name) == texture_map.end()) {

		texture_map[text_name] = std::make_shared<opengl::texture>(glm::vec2(surface->data.ptr()->w,
																					surface->data.ptr()->h),
																   surface->data.ptr()->format->BytesPerPixel,
																   surface->data.ptr()->pixels);

	} else {
		remove_texture(text_name);
		texture_map[text_name] = std::make_shared<opengl::texture>(glm::vec2(surface->data.ptr()->w,
																			 surface->data.ptr()->h),
																   surface->data.ptr()->format->BytesPerPixel,
																   surface->data.ptr()->pixels);
	}


	auto text_size = glm::vec3(surface->data.ptr()->w, surface->data.ptr()->h, 0.0f);

	auto uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	auto render_sprite = std::make_shared<object::sprite>(text->get_origin(),
											 			  text_size,
	                                                      glm::vec4(text->get_color(), 1.0f),
														  uv,
														  load_texture(text_name)->id);

	text->set_render_sprite(render_sprite);

	return text;

}

glm::i32vec2 cw::graphical::video::get_window_size() {
	return window->get_size();
}

std::shared_ptr<cw::graphical::object::model> cw::graphical::video::load_model(const glm::vec3& origin,
																			   const glm::vec3& size,
																			   const std::string& template_file) {

	modules::javascript::json json;
	json.from_file(template_file);

	auto& raw_json = json.data;

	auto model = std::make_shared<graphical::object::model>();

	for (auto t = raw_json["textures"].object_range().begin(); t != raw_json["textures"].object_range().end(); ++t)
	{
		load_texture(t->key(), t->value().as<std::string>());
	}

	std::map<std::string, glm::vec3> sprite_sheet_sizes;
	glm::vec3 final_size;

	for (auto s = raw_json["spritesheets"].object_range().begin(); s != raw_json["spritesheets"].object_range().end(); ++s)
	{
		std::string name = s->key();                        // spritesheet name

		auto s_props = s->value().object_range().begin();

		std::string sprite_size_prop = s_props->key();  // property name.

		glm::vec3 sprite_size(s_props->value()[0].as<double>(), // sprite size.
			s_props->value()[1].as<double>(),
			0.0f);
		if (size.x < 0) {
			sprite_size.x *= glm::abs(size.x / 100.0f);
		}
		else {
			sprite_size.x *= size.x / sprite_size.x;
		}

		if (size.y < 0) {
			sprite_size.y *= glm::abs(size.y / 100.0f);
		}
		else {
			sprite_size.y *= size.y / sprite_size.y;
		}

		/*		    if(size.z < 0){
						size.z = glm::abs(size.z / 100.0f);
					}
		*/

		final_size = sprite_size;

		sprite_sheet_sizes[name] = sprite_size;
	}


	std::map<std::string, std::shared_ptr<graphical::object::sprite> > sprites;

	for (auto s = raw_json["sprites"].object_range().begin(); s != raw_json["sprites"].object_range().end(); ++s)
	{
		std::string name = s->key();                        // sprite name

		auto s_props = s->value().object_range().begin();

		std::string texture = s_props->key();  // mapped texture.


		glm::vec4 uv(s_props->value()[0].as<double>(), // uv coordinates.
			s_props->value()[1].as<double>(),
			s_props->value()[2].as<double>(),
			s_props->value()[3].as<double>());

		sprites[name] = std::make_shared<graphical::object::sprite>(origin,
			sprite_sheet_sizes[texture],
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			uv,
			load_texture(texture)->id);
	}

	std::map<std::string, std::shared_ptr<graphical::object::sprite_animation> > animations;

	for (auto a = raw_json["animations"].object_range().begin(); a != raw_json["animations"].object_range().end(); ++a)
	{

		std::vector<std::shared_ptr<graphical::object::sprite> > frames;

		for (auto f = a->value()["frames"].array_range().begin(); f != a->value()["frames"].array_range().end(); ++f) {
			frames.push_back(sprites[f->as<std::string>()]);
		}

		auto animation = std::make_shared<graphical::object::sprite_animation>();
		animation->duration = a->value()["time"].as<float>();
		animation->frames = frames;

		animations[a->key()] = animation;
	}

	model->set_animations(animations);

	model->change_animation(raw_json["properties"]["default-animation"].as<std::string>());

	model->get_render_sprite_list()["current"] =
		model->get_animations()["current"]->frames[model->get_animations()["current"]->current_frame];

	model->set_origin(origin);
	model->set_size(final_size);

	return model;
}


void cw::graphical::video::unload_model(const std::string& template_file) {
	modules::javascript::json json;
	json.from_file(template_file);

	auto& raw_json = json.data;

	for (auto t = raw_json["textures"].object_range().begin(); t != raw_json["textures"].object_range().end(); ++t)
	{
		remove_texture(t->key());
	}

}
