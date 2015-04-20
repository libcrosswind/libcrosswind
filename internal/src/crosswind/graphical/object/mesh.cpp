#include "crosswind/graphical/object/mesh.hpp"

cw::graphical::object::mesh::mesh(const glm::vec3& c_origin,
								  const glm::vec3& c_size):
origin(c_origin), size(c_size){

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