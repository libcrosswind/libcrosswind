#pragma once

#include <map>
#include <memory>
#include <string>
#include <cstdint>

#include "glm/glm.hpp"

// forward declarations
namespace cw{
namespace graphical{
namespace object{

	class text;
	class model;
	class sprite;

}// namespace object
}// namespace graphical
}// namespace cw

namespace cw{
namespace graphical{
namespace opengl{

	class window;
	class renderer;
	class texture;

}// namespace opengl
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

class video{
public:
	video(const std::string& title,
			  const glm::i32vec2& window_position,
			  const glm::i32vec2& window_resolution,
			  const float& fps,
			  const int& video_flags,
			  const int& window_flags,
	      const bool& resizable);

	~video();

	void set_window_icon(const std::string& path);

	std::shared_ptr< opengl::texture > load_texture(const std::string& name, const std::string& path);

    std::shared_ptr< opengl::texture > load_texture(const std::string& name);

	auto load_font(const std::string& font_path, const uint32_t& size);

	void remove_texture(const std::string& texture_name);

	std::shared_ptr<cw::graphical::object::sprite> 
		load_sprite(const std::string& texture_name, 
					const glm::vec3& size,
					const glm::vec4& uv = glm::vec4(0, 0, 1, 1));

	std::shared_ptr<object::text> load_text(const std::string& text_name,
											const std::string& text_value,
											const glm::vec3& origin,
											const glm::vec3& color,
											const uint32_t& size,
											const std::string& font_path);


	glm::i32vec2 get_window_size();

	

	std::shared_ptr<graphical::object::model> load_model(const glm::vec3& origin,
														 const glm::vec3& size,
														 const std::string& template_file);
	void unload_model(const std::string& template_file);


	std::shared_ptr< opengl::window   >	window;
	std::shared_ptr< opengl::renderer >	renderer;

private:
	std::map<std::string, std::shared_ptr< opengl::texture > > texture_map;
	std::map<std::string, std::shared_ptr< sdl::font       > > font_map;

};// class video

}// namespace graphical
}// namespace cw
