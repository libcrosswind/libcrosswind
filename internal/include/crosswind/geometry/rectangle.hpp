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


			detail::vertex top_right;
			detail::vertex top_left;
			detail::vertex bottom_right;
			detail::vertex bottom_left;

			top_right.set_position(px + dx, py + dy, pz, pw);
			top_right.color = {0.0, 0.0, 1.0, 1.0};

			top_left.set_position(px, py + dy, pz, pw);
			top_left.color = {0.0, 0.0, 1.0, 1.0};
				
			bottom_right.set_position(px + dx, py, pz, pw);
			bottom_right.color = c;

			bottom_left.set_position(px, py, pz, pw);
			bottom_left.color = c;

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

};// class rectangle
