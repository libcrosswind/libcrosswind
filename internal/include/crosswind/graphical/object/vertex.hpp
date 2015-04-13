#pragma once

#include "glm/glm.hpp"

namespace cw{
namespace graphical{
namespace object{

struct vertex{
	glm::vec4 position;
	glm::vec4 color;	
    glm::vec2 uv;

    vertex(const glm::vec4& p, const glm::vec4& c, const glm::vec2& u);

    void set_position(float x, 
                      float y, 
                      float z, 
                      float w);

	void set_position(const glm::vec4& p);

	glm::vec4& get_position();

    void set_color(const float& r, 
                   const float& g, 
                   const float& b, 
                   const float& a);

	void set_alpha(const float& alpha);

	float& get_alpha();

    void set_uv(float u, float v);

};// struct vertex

}// namespace object
}// namespace graphical
}// namespace cw