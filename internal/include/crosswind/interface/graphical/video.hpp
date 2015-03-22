#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <SDL2/SDL_image.h>

//#include <crosswind/simulation/model.hpp>
//#include <crosswind/simulation/gl/gl_texture.hpp>

#include <crosswind/interface/graphical/detail/window.hpp>

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

  /*  virtual void load_texture(const std::string& name, const std::string& path) = 0;

	virtual std::shared_ptr<detail::texture> load_texture(const std::string& name) = 0;

	virtual std::shared_ptr<simulation::model>
			load_model(const glm::vec3& origin, const glm::vec3& size, const std::string& template_file) = 0;
*/
	std::shared_ptr<detail::window>	window;
//    std::shared_ptr<  detail::renderer  >	renderer;

private:
//    std::map<std::string, std::shared_ptr<cw::simulation::gl::gl_texture> > texture_list;

};// class image