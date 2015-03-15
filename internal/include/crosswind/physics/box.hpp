#pragma once

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <crosswind/physics/detail/rigid_body.hpp>

namespace cw{
namespace physics{

		class box;

}// namespace physics
}// namespace cw

class cw::physics::box: public cw::physics::detail::rigid_body{
public:
    box(const float& mass,
        const glm::vec3& origin,
        const glm::vec3& size, 
        const float& s): rigid_body(origin, s){

    		glm::vec3 s_size = size * s;
    		
            init(mass,
                 new btDefaultMotionState(transform),
                 new btBoxShape(btVector3(s_size.x/2, s_size.y/2, s_size.z/2)));
    }

};// class box