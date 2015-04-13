#include "btBulletDynamicsCommon.h"

#include "crosswind/simulation/plane.hpp"

cw::simulation::plane::plane(const glm::vec3& origin,
                 			 const glm::vec3& size,
              			  	 const glm::vec3& scale):
body(origin, scale){

	glm::vec3 s_size = size * scale;

	btTransform transform;
	transform.setOrigin(btVector3(origin.x, origin.y, origin.z));

	init(0.0f,
	     new btDefaultMotionState(transform),
	     new btStaticPlaneShape(btVector3(s_size.x/2, s_size.y/2, s_size.z/2),0));

}