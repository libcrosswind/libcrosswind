#pragma once

#include <string>

#include "SDL2/SDL_mixer.h"
#include "crosswind/modules/functional/resource_property.hpp"

// verify Mix_Chunk forward declaration

namespace cw{
namespace sound{

class chunk{
public:
	chunk(const std::string& file_path);

	functional::resource_property<Mix_Chunk> data;
};// class chunk

}// namespace sound
}// namespace cw