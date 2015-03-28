#pragma once

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <crosswind/implementation/simulation/detail/body.hpp>

namespace cw{
namespace implementation{
namespace simulation{

    class box;

}// namespace simulation
}// namespace implementation
}// namespace cw

class cw::implementation::simulation::box: public cw::implementation::simulation::detail::body{
public:
    box(const glm::vec3& c_origin,
        const glm::vec3& c_size,
        const float&     c_mass,
        const glm::vec3& c_scale      = glm::vec3(1.0f, 1.0f, 1.0f),
        const glm::vec3& c_unit_value = glm::vec3(1.0f, 1.0f, 1.0f)): body(c_origin, c_scale, c_unit_value){

            glm::vec3 s_size = c_size * scale;

            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(origin.x, origin.y, origin.z));

            init(c_mass,
                 new btDefaultMotionState(transform),
                 new btBoxShape(btVector3(s_size.x/2, s_size.y/2, s_size.z/2)));

    }

};// class box