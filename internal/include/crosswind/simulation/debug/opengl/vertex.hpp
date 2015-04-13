#pragma once

#include "glm/glm.hpp"

namespace cw{
namespace simulation{
namespace debug{
namespace opengl{

struct vertex{
	glm::vec4 position;
	glm::vec4 color;	
    glm::vec2 uv;

    vertex(const glm::vec4& p, const glm::vec4& c, const glm::vec2& u);

    void set_position(float x, float y, float z, float w);

	void set_position(const glm::vec4& p);

    void set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    void set_uv(float u, float v);

};// struct vertex

}// namespace opengl
}// namespace debug
}// namespace simulation
}// namespace cw