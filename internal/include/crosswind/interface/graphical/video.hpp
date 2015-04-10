#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <crosswind/interface/graphical/detail/texture.hpp>
#include <crosswind/interface/graphical/detail/window.hpp>
#include <crosswind/interface/graphical/detail/renderer.hpp>
#include <crosswind/interface/graphical/object/text.hpp>
#include <crosswind/interface/graphical/object/model.hpp>

namespace cw{
namespace interface{
namespace graphical{

  class video;

}// namespace graphical
}// namespace interface
}// namespace cw

class cw::interface::graphical::video{
public:
	video() {
	}

	virtual ~video(){

	}

    virtual void load_texture(const std::string& name, const std::string& path) = 0;
	virtual std::shared_ptr<detail::texture> load_texture(const std::string& name) = 0;

	virtual void set_window_icon(const std::string& path) = 0;

	virtual std::shared_ptr<object::text> load_text(const std::string& text_name,
													const std::string& text,
													const glm::vec3& origin,
													const glm::vec4& color,
													const uint32_t& size,
													const std::string& font_path) = 0;


	virtual std::shared_ptr<object::model>
			load_model(const glm::vec3& origin, const glm::vec3& size, const std::string& template_file) = 0;

	std::shared_ptr< detail::window   >	window;
    std::shared_ptr< detail::renderer >	renderer;

protected:
	std::map<std::string, std::shared_ptr<detail::texture> > texture_map;

};// class image