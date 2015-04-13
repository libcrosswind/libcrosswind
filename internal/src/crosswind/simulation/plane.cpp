#include "btBulletDynamicsCommon.h"

#include "crosswind/physics/plane.hpp"

cw::physics::plane::plane(const glm::vec3& origin,
              			  const glm::vec3& size, 
              			  const glm::vec3& scale): 
rigid_body(origin, scale){

    		glm::vec3 s_size = size * scale;

			init(0.0f,
                 new btDefaultMotionState(transform),
				 new btStaticPlaneShape(btVector3(s_size.x/2, s_size.y/2, s_size.z/2),0));

}