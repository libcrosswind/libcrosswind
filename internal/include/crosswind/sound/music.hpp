#pragma once

#include <string>

#include <SDL_mixer.h>
#include "crosswind/modules/functional/resource_property.hpp"

// verify Mix_Music forward declaration

namespace cw{
namespace sound{

class music{
public:
	music(const std::string& file_path);

	functional::resource_property<Mix_Music> data;

};// class music

}// namespace sound
}// namespace cw
