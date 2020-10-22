#pragma once

#include <cstdint>

#include "glm/glm.hpp"

namespace cw{
namespace graphical{
namespace opengl{

class texture{
public:
	texture(const glm::vec2& size, unsigned char bpp, void* pixels);

    ~texture();

	uint32_t id;

	glm::vec2 size;

};// class texture

}// namespace opengl
}// namespace graphical
}// namespace cw
 