#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include "glm/glm.hpp"

// forward declarations
namespace cw{
namespace graphical{
namespace object{
	
	class sprite;

}// namespace object
}// namespace graphical
}// namespace cw

namespace cw{
namespace graphical{
namespace sdl{
	
	class font;

}// namespace sdl
}// namespace graphical
}// namespace cw

namespace cw{
namespace graphical{
namespace object{

class text{
public:
	text(const std::string& c_text = "text",
		 const glm::vec3& c_origin = glm::vec3(0.0f, 0.0f, 0.0f),
		 const glm::vec3& c_color = glm::vec3(1.0f, 1.0f, 1.0f),
		 const uint32_t& c_size = 24);

	void set_text(const std::string& f_text);

	std::string& get_text();

	void set_origin(const glm::vec3& f_origin);

	glm::vec3 get_origin();

	void set_size(const uint32_t& f_size);

	uint32_t get_size();

	void set_color(const glm::vec3& f_color);

	glm::vec3 get_color();

	void set_render_sprite(std::shared_ptr<sprite> sprite);

	auto get_render_sprite();

	auto render(std::shared_ptr<sdl::font> font);

private:
	std::string text_value;
	glm::vec3 origin;
	glm::vec3 color;
	uint32_t size;

	std::shared_ptr<object::sprite> render_sprite;

};// class text

}// namespace object
}// namespace graphical
}// namespace cw
