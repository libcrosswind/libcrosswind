#pragma once

#include <glm/glm.hpp>

namespace cw{
namespace interface{
namespace simulation{
namespace debug{

	struct vertex;

}// namespace debug
}// namespace simulation
}// namespace interface
}// namespace cw

struct cw::interface::simulation::debug::vertex{
	glm::vec4 position;
	glm::vec4 color;	
    glm::vec2 uv;

    vertex(const glm::vec4& p, const glm::vec4& c, const glm::vec2& u):
    position(p), color(c), uv(u){

    }

    void set_position(float x, float y, float z, float w){
    	position.x = x;
    	position.y = y;
    	position.z = z;
    	position.w = w;
    }

	void set_position(const glm::vec4& p){
		position = p;
	}

    void set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
    	color.r = r;
    	color.g = g;
    	color.b = b;
    	color.a = a;
    }

    void set_uv(float u, float v){
    	uv.x = u;
    	uv.y = v;
    }

};// struct vertex