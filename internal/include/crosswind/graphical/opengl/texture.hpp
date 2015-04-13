#pragma once

#include <cstdint>

namespace cw{
namespace graphical{
namespace opengl{

class cw::implementation::graphical::opengl::texture: public cw::interface::graphical::detail::texture{
public:
	texture(const glm::vec2& size, unsigned char bpp, void* pixels);

    ~texture();

	uint32_t id;

};// class texture

}// namespace opengl
}// namespace graphical
}// namespace cw
 