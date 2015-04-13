#include "btBulletDynamicsCommon.h"

#include "crosswind/simulation/detail/character.hpp"

cw::simulation::detail::character::character(const glm::vec3& c_origin,
                                             const glm::vec2& c_size,
                                             const glm::vec3& c_scale,
                                             const glm::vec3& c_unit_value,
                                             const float& c_step_height): 
origin(c_origin),
size(c_size), 
scale(c_scale), 
unit_value(c_unit_value), 
step_height(c_step_height),
speed(0.0f, 0.0f, 0.0f){

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

void cw::simulation::detail::character::set_origin(const glm::vec3& new_origin){
    origin  = new_origin;
    origin *= scale;
    btTransform transform;
    transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
    ghost_object->setWorldTransform(transform);
}

glm::vec3 cw::simulation::detail::character::get_origin(){
    btVector3 ghost_origin;
    ghost_origin = ghost_object->getWorldTransform().getOrigin();

    origin.x = ghost_origin[0];
    origin.y = ghost_origin[1];
    origin.z = ghost_origin[2];

    origin/=scale;

    return origin;
}

void cw::simulation::detail::character::set_jump_speed(const float& spd){
    character_object->setJumpSpeed(spd*unit_value.y);
}

void cw::simulation::detail::character::jump(){
    character_object->jump();
}

void cw::simulation::detail::character::set_speed(const glm::vec3& spd){
    speed = spd;
    speed *= scale;
    character_object->setWalkDirection(btVector3(speed.x, speed.y, speed.z));
}

glm::vec3 cw::simulation::detail::character::get_speed(){
    return speed/scale;
}

bool cw::simulation::detail::character::on_ground(){
    return character_object->onGround();
}

void* cw::simulation::detail::character::get_character_object(){
    return character_object.get();
}