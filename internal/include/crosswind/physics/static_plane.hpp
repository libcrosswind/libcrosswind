#pragma once

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <crosswind/physics/detail/rigid_body.hpp>

namespace cw{
namespace physics{
	
	class static_plane;

}// namespace physics
}// namespace cw

class cw::physics::static_plane: public cw::physics::detail::rigid_body{
	public:
		static_plane(const glm::vec3& origin,
                     const glm::vec3& size): rigid_body(origin){

			init(0.0f,
                 new btDefaultMotionState(transform),
				 new btStaticPlaneShape(btVector3(size.x, size.y, size.z),0));

		}

};// class static_plane