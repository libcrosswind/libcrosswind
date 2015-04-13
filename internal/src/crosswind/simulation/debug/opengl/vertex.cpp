#include "crosswind/simulation/debug/opengl/vertex.hpp"

cw::simulation::debug::opengl::vertex::vertex(const glm::vec4& p, 
                                              const glm::vec4& c, 
                                              const glm::vec2& u):
position(p), color(c), uv(u){


}

void cw::simulation::debug::opengl::vertex::set_position(float x, 
                                                         float y, 
                                                         float z, 
                                                         float w){

	position.x = x;
	position.y = y;
	position.z = z;
	position.w = w;

}

void cw::simulation::debug::opengl::vertex::set_position(const glm::vec4& p){

	position = p;

}

void cw::simulation::debug::opengl::vertex::set_color(unsigned char r, 
                                                      unsigned char g, 
                                                      unsigned char b, 
                                                      unsigned char a){

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

}

void cw::simulation::debug::opengl::vertex::set_uv(float u, float v){
	
    uv.x = u;
	uv.y = v;

}

