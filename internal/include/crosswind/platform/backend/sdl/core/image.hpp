#pragma once

#include <SDL2/SDL_image.h>

#include <crosswind/javascript/json.hpp>
#include <crosswind/platform/backend/interface/core/image.hpp>
#include <crosswind/platform/backend/sdl/core/exception.hpp>
#include <crosswind/platform/backend/sdl/video/surface.hpp>
#include <crosswind/platform/filesystem.hpp>

#include <crosswind/simulation/sprite_animation.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace sdl{
namespace core{

  class image;

}// namespace core
}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::sdl::core::image: public cw::platform::backend::interface::core::image{
public:
	image(int flags) {
		if ((IMG_Init(flags) & flags) != flags)
		  throw exception("IMG_Init");
	}

	// non-copyable
	image(const image& other) = delete;
	image& operator=(const image& other) = delete;

	// non-movable
	image(image&& other) = delete;
	image& operator=(image&& other) = delete;

	virtual ~image() {
		IMG_Quit();
	}

	int init_more(int flags) {
	int ret;
		if (((ret = IMG_Init(flags)) & flags) != flags)
		  throw exception("IMG_Init");
		return ret;
	}

	int init_flags() {
		return IMG_Init(0);
	}

    void load_texture(const std::string& name, const std::string& path){

	    if ( texture_list.find(name) == texture_list.end()) {
		    auto surface = std::make_unique<video::surface>(platform::filesystem::get_file_path(path));

		    texture_list[name] = std::make_shared<simulation::gl::gl_texture>
				    (glm::vec2(surface->data.ptr()->w, surface->data.ptr()->h),
						    surface->data.ptr()->format->BytesPerPixel,
						    surface->data.ptr()->pixels);


	    }

    }

    std::shared_ptr<simulation::gl::gl_texture> load_texture(const std::string& name){
        
        return texture_list[name];

    }


	std::shared_ptr<simulation::model> load_model(const glm::vec3& origin, const glm::vec3& size, const std::string& template_file){

		cw::javascript::json json;
		json.from_file(template_file);

		auto& raw_json = json.data;

		auto model = std::make_shared<simulation::model>();

		for (auto t = raw_json["textures"].begin_members(); t != raw_json["textures"].end_members(); ++t)
		{
			load_texture(t->name(), t->value().as<std::string>());
		}

		std::map<std::string, std::shared_ptr<simulation::sprite> > sprites;

		for (auto s = raw_json["sprites"].begin_members(); s != raw_json["sprites"].end_members(); ++s)
		{
			std::string name    = s->name();                        // sprite name

			auto s_props = s->value().begin_members();

			std::string texture = s_props->name();  // mapped texture.


			glm::vec4 uv(s_props->value()[0].as<double>(), // uv coordinates.
					 	 s_props->value()[1].as<double>(),
				 		 s_props->value()[2].as<double>(),
						 s_props->value()[3].as<double>());

			std::cout << "Sprite: " << name << std::endl;
			std::cout << "Texture id: " << load_texture(texture)->id << std::endl;

			std::cout << "X: " << uv.x << " Y: " << uv.y << " Z: " << uv.z << " W: " << uv.w << std::endl;

			sprites[name] = std::make_shared<simulation::sprite>(origin, size, uv, load_texture(texture)->id);
		}

		std::map<std::string, std::shared_ptr<simulation::sprite_animation> > animations;

		for (auto a = raw_json["animations"].begin_members(); a != raw_json["animations"].end_members(); ++a)
		{

			std::vector<std::shared_ptr<simulation::sprite> > frames;

			for(auto f = a->value()["frames"].begin_elements(); f != a->value()["frames"].end_elements();  ++f){
				frames.push_back(sprites[f->as<std::string>()]);
			}

			auto animation = std::make_shared<simulation::sprite_animation>();
			animation->duration = a->value()["time"].as<double>();
			animation->frames = frames;

			animations[a->name()] = animation;
		}

		model->get_animations() = animations;

		for(auto m : model->get_animations()){
			std::cout << "Animation name: \t\t" << m.first << std::endl;
			std::cout << "Animation duration: \t\t" << m.second->duration << std::endl;
			std::cout << "Animation frames: \t\t" << m.second->frames.size() << std::endl;

		}

		std::cout << "Default animation: " << raw_json["properties"]["default-animation"].as<std::string>() << std::endl;

		model->change_animation(raw_json["properties"]["default-animation"].as<std::string>());

		model->set_origin(origin);
		model->set_size(size);

		return model;
	}

};
 