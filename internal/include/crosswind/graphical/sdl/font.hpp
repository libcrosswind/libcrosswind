#pragma once 

#include <string>
#include <cstdint>

#include <SDL_ttf.h>

#include "crosswind/modules/functional/resource_property.hpp"

// verify TT_Font forward declaration

namespace cw{
namespace graphical{
namespace sdl{

class font{
public:
	font(const std::string& file_path, const uint32_t& size);

	functional::resource_property<TTF_Font> data;

};// class font

}// namespace sdl
}// namespace graphical
}// namespace cw
