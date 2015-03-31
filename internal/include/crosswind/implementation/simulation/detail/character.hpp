#pragma once

#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <glm/glm.hpp>

namespace cw{
namespace implementation{
namespace simulation{
namespace detail{

	class character;

}// namespace detail
}// namespace simulation
}// namespace implementation
}// namespace cw

class cw::implementation::simulation::detail::character: public cw::interface::simulation::detail::character{
public:
    character(const glm::vec3& c_origin,
              const glm::vec2& c_size,
              const glm::vec3& c_scale,
              const glm::vec3& c_unit_value,
              const float& c_step_height):
        interface::simulation::detail::character(c_origin, c_size, c_scale, c_unit_value, c_step_height){

            origin *= scale;

            size *= glm::vec2(scale.x, scale.y);

            btTransform start_transform;
            start_transform.setIdentity ();
            start_transform.setOrigin (btVector3(origin.x, origin.y, origin.z));

            ghost_object = std::make_unique<btPairCachingGhostObject>();
            ghost_object->setWorldTransform(start_transform);

            capsule = std::make_unique<btCapsuleShape>(size.x/2, size.y/2);

            ghost_object->setCollisionShape (capsule.get());
            ghost_object->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

            character_object = std::make_unique<btKinematicCharacterController> (ghost_object.get(), 
                                                                                 capsule.get(), 
                                                                                 step_height);

    }

    virtual void set_origin(const glm::vec3& new_origin){
        origin  = new_origin;
        origin *= scale;
        btTransform transform;
        transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
        ghost_object->setWorldTransform(transform);
    }

    virtual glm::vec3 get_origin(){
        btVector3 ghost_origin;
        ghost_origin = ghost_object->getWorldTransform().getOrigin();

        origin.x = ghost_origin[0];
        origin.y = ghost_origin[1];
        origin.z = ghost_origin[2];

        origin/=scale;

        return origin;
    }

    virtual void set_jump_speed(const float& spd){
        character_object->setJumpSpeed(spd*unit_value.y);
    }

    virtual void jump(){
        character_object->jump();
    }

    virtual void set_speed(const glm::vec3& spd){
        speed = spd;
        speed *= scale;
        character_object->setWalkDirection(btVector3(speed.x, speed.y, speed.z));
    }

    virtual glm::vec3 get_speed(){
        return speed/scale;
    }

    bool on_ground(){
        return character_object->onGround();
    }

    void* get_character_object(){
        return character_object.get();
    }

public:
    std::unique_ptr<btKinematicCharacterController> character_object;
    std::unique_ptr<btPairCachingGhostObject> ghost_object;
    std::unique_ptr<btConvexShape> capsule;

};// class character