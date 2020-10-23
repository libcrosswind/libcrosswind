/*#include "bullet/btBulletDynamicsCommon.h"

#include "crosswind/simulation/box.hpp"

cw::simulation::box::box(const glm::vec3& c_origin,
                         const glm::vec3& c_size,
                         const float&     c_mass,
                         const glm::vec3& c_scale,
                         const glm::vec3& c_unit_value):
body(c_origin, c_scale, c_unit_value){

            glm::vec3 s_size = c_size * scale;

            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(origin.x, origin.y, origin.z));

            init(c_mass,
                 new btDefaultMotionState(transform),
                 new btBoxShape(btVector3(s_size.x/2, s_size.y/2, s_size.z/2)));

}
*/