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
        const glm::vec3& size): rigid_body(origin){

            init(mass,
                 new btDefaultMotionState(transform),
                 new btBoxShape(btVector3(size.x, size.y, size.z)));
    }

};// class box