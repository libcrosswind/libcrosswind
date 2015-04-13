#include "crosswind/graphical/object/mesh.hpp"

cw::graphical::object::mesh::mesh(const glm::vec3& o, 
								  const glm::vec3& s):
origin(o), size(s){

}

void cw::graphical::object::mesh::set_size(const glm::vec3& new_size){ 

	size = new_size; 
}

glm::vec3 cw::graphical::object::mesh::get_size(){ 

	return size; 

}

void cw::graphical::object::mesh::set_origin(const glm::vec3& new_origin){ 

	origin = new_origin; 

}

glm::vec3 cw::graphical::object::mesh::get_origin(){ 

	return origin; 

}


void cw::graphical::object::mesh::set_vertices(const std::vector<cw::graphical::object::vertex>& new_vertices){

	vertices = new_vertices; 

}

std::vector<cw::graphical::object::vertex>& cw::graphical::object::mesh::get_vertices(){

	return vertices; 

}