#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include <crosswind/interface/graphical/detail/sprite.hpp>
#include <crosswind/implementation/graphical/sdl/font.hpp>
#include <crosswind/implementation/graphical/sdl/surface.hpp>

namespace cw{
namespace interface{
namespace graphical{
namespace object{
	
	class text;

}// namespace object
}// namespace graphical
}// namespace interface
}// namespace cw

class cw::interface::graphical::object::text{
public:
	text(const std::string& c_name = "undefined",
		 const std::string& c_text = "text",
		 const glm::vec3& c_origin = glm::vec3(0.0f, 0.0f, 0.0f),
		 const uint32_t& c_size = 24,
		 const glm::vec4& c_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)){

		name = c_name;
		text_value = c_text;
		origin = c_origin;
		size = c_size;
		color = c_color;

	}

	void set_name(const std::string& f_name){
		name = f_name;
	}

	std::string& get_name(){
		return name;
	}

	void set_text(const std::string& f_text){
		text_value = f_text;
	}

	std::string& get_text(){
		return text_value;
	}

	void set_origin(const glm::vec3& f_origin){
		origin = f_origin;
	}

	glm::vec3 get_origin(){
		return origin;
	}

	void set_size(const uint32_t& f_size){
		size = f_size;
	}

	uint32_t get_size(){
		return size;
	}

	void set_color(const glm::vec4& f_color){
		color = f_color;
	}

	glm::vec4 get_color(){
		return color;
	}

	void set_render_sprite(std::shared_ptr<detail::sprite> sprite){
		render_sprite = sprite;
	}

	std::shared_ptr<detail::sprite> get_render_sprite(){
		return render_sprite;
	}

	auto render(std::shared_ptr<implementation::graphical::sdl::font> font){
		SDL_Color text_color = {uint8_t(color.r * 255),
								uint8_t(color.g * 255),
								uint8_t(color.b * 255)};

		auto surface =
				std::make_shared<implementation::graphical::sdl::surface>(font->data.ptr(), text_value, text_color);

		return surface;
	};


private:
	std::string name;
	std::string text_value;
	glm::vec3 origin;
	glm::vec4 color;
	uint32_t size;

	std::shared_ptr<detail::sprite> render_sprite;
};