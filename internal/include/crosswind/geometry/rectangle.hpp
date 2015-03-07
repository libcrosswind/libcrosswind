#pragma once

#include <utility>

#include <glm/glm.hpp>

#include <crosswind/geometry/detail/mesh.hpp>

namespace cw {
namespace geometry{

	class rectangle;

}// namespace geometry
}// namespace cw

class cw::geometry::rectangle: public cw::geometry::detail::mesh{
public:	
	rectangle(const glm::vec3& p, const glm::vec3& s, const glm::vec4& c):
		mesh(p, s){

			auto px = p[0];
			auto py = p[1];
			auto pz = p[2];
			auto pw = 1.0;

			auto w = s[0];
			auto h = s[1];
			auto d = s[2];

			auto tr = std::make_pair(glm::vec4(px + w, py + h, pz, pw), c);
			auto tl = std::make_pair(glm::vec4(px, py + h, pz, pw), c);
			auto br = std::make_pair(glm::vec4(px+w, py, pz, pw), c);
			auto bl = std::make_pair(glm::vec4(px, py, pz, pw), c);

			vertices = {
				// First triangle
				tr,
				tl,
				bl,
				//Second triangle
				bl,
				br,
				tr
			};

 	}

};// class rectangle
