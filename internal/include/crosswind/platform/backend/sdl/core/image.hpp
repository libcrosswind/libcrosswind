#pragma once

#include <SDL2/SDL_image.h>

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

	~image() {
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
        auto surface = std::make_unique<video::surface>(platform::filesystem::get_file_path(path));

        texture_list[name] = std::make_shared<simulation::gl::gl_texture>
                (glm::vec2(surface->data.ptr()->w, surface->data.ptr()->h),
                        surface->data.ptr()->format->BytesPerPixel,
                        surface->data.ptr()->pixels);
    }

    std::shared_ptr<simulation::gl::gl_texture> load_texture(const std::string& name){
        
        return texture_list[name];

    }

	std::shared_ptr<simulation::model> load_model(const glm::vec3& origin, const glm::vec3& size, const std::string& template_file){

		cw::javascript::json json;
		json.from_file(template_file);

		auto& raw_json = json.data;


		for (auto t = raw_json["textures"].begin_members(); t != raw_json["textures"].end_members(); ++t)
		{
			load_texture(t->name().as<std::string>(), t->value().as<std::string>());
		}

		/*			auto sprite_animation = std::make_shared<simulation::sprite_animation>();

			sprite_animation */

		std::map[];

		for (auto s = raw_json["sprites"].begin_members(); s != raw_json["sprites"].end_members(); ++s)
		{
			s->name().as<std::string>();         // sprite name
			s->value().name().as<std::string>(); // mapped texture.

			glm::vec4 uv(s->value().value()[0].as<float>(), // uv coordinates.
						 s->value().value()[1].as<float>(),
					     s->value().value()[2].as<float>(),
					     s->value().value()[3].as<float>());

/*			const glm::vec3& p,
			const glm::vec3& s,
			const glm::vec4& uv,
			const uint32_t& t_id):*/
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

		model->animations["current"] 
		animations["current"] = animations[raw_json["properties"]["default-animation"].as<std::string>()];

		return model;
	}

};
 