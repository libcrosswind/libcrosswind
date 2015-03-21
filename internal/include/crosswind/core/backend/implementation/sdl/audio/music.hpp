#pragma once

#include <SDL2/SDL_mixer.h>
#include <crosswind/functional/resource_property.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace sdl{
namespace audio{

	class music;

}// namespace audio
}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::sdl::audio::music{
public:
	music(const std::string& file_path): data(Mix_LoadMUS, Mix_FreeMusic, file_path.c_str()) {

	}

	functional::resource_property<Mix_Music> data;

};// class music