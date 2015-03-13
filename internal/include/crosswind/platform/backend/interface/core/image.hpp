#pragma once

#include <map>
#include <string>

#include <SDL2/SDL_image.h>

#include <crosswind/simulation/gl/gl_texture.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace interface{
namespace core{

  class image;

}// namespace core
}// namespace interface
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::interface::core::image{
protected:
	image() {

	}

	// non-copyable
	image(const image& other) = delete;
	image& operator=(const image& other) = delete;

	// non-movable
	image(image&& other) = delete;
	image& operator=(image&& other) = delete;

public:
	virtual ~image() {

	}

    virtual void load_texture(const std::string& name, const std::string& path) = 0;
    virtual std::shared_ptr<cw::simulation::gl::gl_texture> load_texture(const std::string& name) = 0;

    std::map<std::string, std::shared_ptr<cw::simulation::gl::gl_texture> > texture_list;

};// class image