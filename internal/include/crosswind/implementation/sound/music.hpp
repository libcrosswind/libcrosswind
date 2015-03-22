#pragma once

#include <SDL2/SDL_mixer.h>
#include <crosswind/modules/functional/resource_property.hpp>

namespace cw{
namespace implementation{
namespace sound{

	class music;

}// namespace sound
}// namespace implementation
}// namespace cw

class cw::implementation::sound::music{
public:
	music(const std::string& file_path): data(Mix_LoadMUS, Mix_FreeMusic, file_path.c_str()) {

	}

	functional::resource_property<Mix_Music> data;

};// class music