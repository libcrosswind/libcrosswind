#pragma once

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <crosswind/physics/detail/rigid_body.hpp>

namespace cw{
namespace physics{

	class sphere;

}// namespace physics
}// namespace cw

class cw::physics::sphere: public cw::physics::detail::rigid_body{
	sphere(const float& mass,
           const glm::vec3& origin,
           const float& radius): rigid_body(origin){

			init(mass,
				new btDefaultMotionState(transform),
				new btSphereShape(btScalar(radius)));

	}
	
};// class sphere