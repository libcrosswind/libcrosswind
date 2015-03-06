#pragma once

#include <crosswind/math/vector3.hpp>
#include <crosswind/simulation/detail/object.hpp>

namespace cw {
namespace geometry{

	class rectangle;

}// namespace geometry
}// namespace cw

class cw::geometry::rectangle: public cw::simulation::detail::object{
public:	
	rectangle(const math::vector3& p, const math::vector3& s):
		object(p, s){

			vertices = {
				// First triangle
				p[0] + s[0],		// x
				p[1] + s[1],		// y
				p[2],				// z

				p[0],				// x
				p[1] + s[1],		// y
				p[2],				// z

				p[0],				// x
				p[1],				// y
				p[2],				// z

				//Second triangle
				p[0],				// x
				p[1],				// y
				p[2],				// z

				p[0] + s[0],		// x
				p[1],				// y
				p[2],				// z

				p[0] + s[0],		// x
				p[1] + s[1],		// y
				p[2]				// z
			};

 	}

};// class rectangle
