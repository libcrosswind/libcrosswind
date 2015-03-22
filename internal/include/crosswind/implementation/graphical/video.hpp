#pragma once

#include <memory>

#include <SDL2/SDL_image.h>

#include <crosswind/interface/graphical/video.hpp>
#include <crosswind/implementation/platform/exception.hpp>
#include <crosswind/implementation/graphical/opengl/window.hpp>

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

//		renderer = std::make_shared<detail::renderer>();
	}

	virtual ~video() {
		IMG_Quit();
	}

/*    void load_texture(const std::string& name, const std::string& path){

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
*/
private:
	int init_more(int flags) {
		int ret;
			if (((ret = IMG_Init(flags)) & flags) != flags)
		  		throw platform::exception("IMG_Init");
		return ret;
	}

};// class video