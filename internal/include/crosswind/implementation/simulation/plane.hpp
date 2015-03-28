#pragma once

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <crosswind/physics/detail/rigid_body.hpp>

namespace cw{
namespace physics{
	
	class plane;

}// namespace physics
}// namespace cw

class cw::physics::plane: public cw::physics::detail::rigid_body{
	public:
		plane(const glm::vec3& origin,
              const glm::vec3& size, 
              const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)): rigid_body(origin, scale){

    		glm::vec3 s_size = size * scale;

			init(0.0f,
                 new btDefaultMotionState(transform),
				 new btStaticPlaneShape(btVector3(s_size.x/2, s_size.y/2, s_size.z/2),0));

		}

};// class plane