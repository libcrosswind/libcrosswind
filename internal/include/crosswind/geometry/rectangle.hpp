#pragma once

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

			auto x = p[0];
			auto y = p[1];
			auto z = p[2];
			auto w = 1.0;

			auto w = s[0];
			auto h = s[1];
			auto d = s[2];

			auto tr = std::make_pair(glm::vec4(x + w, y + h, z, w), c);
			auto tl = std::make_pair(glm::vec4(x, y + h, z, w), c);
			auto br = std::make_pair(glm::vec4(x+w, y, z, w), c);
			auto bl = std::make_pair(glm::vec4(x, y, z, w), c);

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
