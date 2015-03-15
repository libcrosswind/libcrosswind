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
        const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)): rigid_body(origin, scale){

    		glm::vec3 s_size = size * scale;
    		
            init(mass,
                 new btDefaultMotionState(transform),
                 new btBoxShape(btVector3(s_size.x/2, s_size.y/2, s_size.z/2)));
    }

};// class box