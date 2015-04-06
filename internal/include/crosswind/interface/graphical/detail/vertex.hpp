#pragma once

#include <glm/glm.hpp>

namespace cw{
namespace interface{
namespace graphical{
namespace detail{

	struct vertex;

}// namespace detail
}// namespace graphical
}// namespace interface
}// namespace cw

struct cw::interface::graphical::detail::vertex{
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

	glm::vec4& get_position(){
		return position;
	}

    void set_color(const float&  r, const float& g, const float& b, const float& a){
    	color.r = r;
    	color.g = g;
    	color.b = b;
    	color.a = a;
    }

	void set_alpha(const float& alpha) {
		color.a = alpha;
	}

	float& get_alpha(){
		return color.a;
	}

    void set_uv(float u, float v){
    	uv.x = u;
    	uv.y = v;
    }

};// struct vertex