#pragma once

#include <memory>

#include <crosswind/interface/graphical/video.hpp>
#include <crosswind/implementation/platform/exception.hpp>
#include <crosswind/implementation/graphical/opengl/window.hpp>
#include <crosswind/implementation/graphical/opengl/renderer.hpp>
#include <crosswind/implementation/graphical/opengl/texture.hpp>
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
		  const glm::i32vec2 window_position,
		  const glm::i32vec2 window_resolution,
		  const float& fps,
		  const int& image_flags,
		  const int& window_flags) {

		if ((IMG_Init(image_flags) & image_flags) != image_flags)
		  throw platform::exception("IMG_Init");

        window = std::make_shared<opengl::window>(title,
		                                          window_position,
		                                          window_resolution,
		                                          fps,
		                                          window_flags);

		renderer = std::make_shared<opengl::renderer>();
	}

	virtual ~video() {
		IMG_Quit();
	}

    void load_texture(const std::string& name, const std::string& path){

        if ( texture_list.find(name) == texture_list.end()) {
            auto surface = std::make_unique<sdl::surface>(path);

            texture_list[name] = std::make_shared<opengl::texture>
                    (glm::vec2(surface->data.ptr()->w, surface->data.ptr()->h),
                            surface->data.ptr()->format->BytesPerPixel,
                            surface->data.ptr()->pixels);
        }

    }

    std::shared_ptr<interface::graphical::detail::texture> load_texture(const std::string& name){
        
        return texture_list[name];
        
    }

};// class video