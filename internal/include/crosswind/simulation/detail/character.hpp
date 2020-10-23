/*#pragma once

#include <memory>

#include "bullet/BulletDynamics/Character/btKinematicCharacterController.h"
#include "bullet/BulletCollision/CollisionDispatch/btGhostObject.h"
#include "glm/glm.hpp"

namespace cw{
namespace simulation{
namespace detail{

class character{
public:
    character(const glm::vec3& c_origin,
              const glm::vec2& c_size,
              const glm::vec3& c_scale,
              const glm::vec3& c_unit_value,
              const float& c_step_height);

    void set_origin(const glm::vec3& new_origin);

    glm::vec3 get_origin();

    void set_jump_speed(const float& spd);

    void jump();

    void set_speed(const glm::vec3& spd);

    glm::vec3 get_speed();

    bool on_ground();

    void* get_character_object();

protected:
    glm::vec3 origin;
    glm::vec2 size;
    glm::vec3 scale;
    glm::vec3 unit_value;
    float step_height;
    glm::vec3 speed;

public:
    std::unique_ptr<btKinematicCharacterController> character_object;
    std::unique_ptr<btPairCachingGhostObject> ghost_object;
    std::unique_ptr<btConvexShape> capsule;

};// class character

}// namespace detail
}// namespace simulation
}// namespace cw

*/