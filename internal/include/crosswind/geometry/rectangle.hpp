#pragma once

#include <utility>

#include <glm/glm.hpp>

#include <crosswind/geometry/detail/mesh.hpp>
#include <crosswind/geometry/detail/vertex.hpp>

namespace cw {
namespace geometry{

	class rectangle;

}// namespace geometry
}// namespace cw

class cw::geometry::rectangle: public cw::geometry::detail::mesh{
public:	
	rectangle(const glm::vec3& p, const glm::vec3& s, const glm::vec4& c = glm::vec4(1.0,1.0,1.0,1.0)):
			cw::geometry::detail::mesh(p, s){

    		auto px = p.x - s.x/2;
			auto py = p.y - s.y/2;
			auto pz = p.z - s.z/2;
			auto pw = 1.0f;

			auto dx = s.x;
			auto dy = s.y;
			auto dz = s.z;


			detail::vertex top_right(glm::vec4(px + dx, py + dy, pz, pw), c, glm::vec2(0.0, 0.0));
			detail::vertex top_left(glm::vec4(px, py + dy, pz, pw), c, glm::vec2(0.0));
			detail::vertex bottom_right(glm::vec4(px + dx, py, pz, pw), c, glm::vec2(0.0));
			detail::vertex bottom_left(glm::vec4(px, py, pz, pw), c, glm::vec2(0.0));

			vertices = {
				// First triangle
				top_right,
				top_left,
				bottom_left,
				//Second triangle
				bottom_left,
				bottom_right,
				top_right
			};

 	}

	glm::vec3 set_origin(const glm::vec3& new_origin){

		auto px = new_origin.x - size.x/2;
		auto py = new_origin.y - size.y/2;
		auto pz = new_origin.z - size.z/2;
		auto pw = 1.0f;

		auto dx = size.x;
		auto dy = size.y;
		auto dz = size.z;

		glm::vec4 top_right (px + dx, py + dy, pz, pw);
		glm::vec4 top_left(px, py + dy, pz, pw);
		glm::vec4 bottom_right(px + dx, py, pz, pw);
		glm::vec4 bottom_left(px, py, pz, pw);

		vertices[0].set_position(top_right);
		vertices[1].set_position(top_left);
		vertices[2].set_position(bottom_left);

		vertices[3].set_position(bottom_left);
		vertices[4].set_position(bottom_right);
		vertices[5].set_position(top_right);

		origin = new_origin;

	}

	glm::vec3 get_origin(){

		return origin;
	}




};// class rectangle
