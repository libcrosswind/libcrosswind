#pragma once

#include <SDL2/SDL_image.h>

#include <crosswind/platform/backend/interface/core/image.hpp>
#include <crosswind/platform/backend/sdl/core/exception.hpp>
#include <crosswind/platform/backend/sdl/video/surface.hpp>
#include <crosswind/platform/filesystem.hpp>

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
        auto surface = std::make_unique<video::surface>(cw::platform::filesystem::get_file_path(path));

        texture_list[name] = std::make_shared<cw::simulation::gl::gl_texture>
                (glm::vec2(surface->data.ptr()->w, surface->data.ptr()->h),
                        surface->data.ptr()->format->BytesPerPixel,
                        surface->data.ptr()->pixels);


    }


};
 