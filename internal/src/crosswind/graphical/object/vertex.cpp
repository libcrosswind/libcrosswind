#include "crosswind/graphical/object/vertex.hpp"

cw::graphical::object::vertex::vertex(const glm::vec4& p, 
									  const glm::vec4& c, 
									  const glm::vec2& u):
position(p), 
color(c), 
uv(u){

}

void cw::graphical::object::vertex::set_position(float x, 
												 float y, 
												 float z, 
												 float w){
	
	position.x = x;
	position.y = y;
	position.z = z;
	position.w = w;

}

void cw::graphical::object::vertex::set_position(const glm::vec4& p){
	
	position = p;

}

glm::vec4& cw::graphical::object::vertex::get_position(){

	return position;

}

void cw::graphical::object::vertex::set_color(const float& r, 
											  const float& g, 
											  const float& b, 
											  const float& a){

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

}

void cw::graphical::object::vertex::set_alpha(const float& alpha) {

	color.a = alpha;

}

float& cw::graphical::object::vertex::get_alpha(){

	return color.a;

}

void cw::graphical::object::vertex::set_uv(float u, float v){

	uv.x = u;
	uv.y = v;

}
