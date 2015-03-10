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
		mesh(p, s){

			auto px = p.x;
			auto py = p.y;
			auto pz = p.z;
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

	void set_position(const glm::vec3& p){

		auto px = p.x;
		auto py = p.y;
		auto pz = p.z;
		auto pw = 1.0f;

		auto dx = size.x;
		auto dy = size.y;
		auto dz = size.z;

		glm::vec4 c = glm::vec4(1.0,1.0,1.0,1.0);
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

	glm::vec3 get_position(){
		return position;
	}
};// class rectangle
