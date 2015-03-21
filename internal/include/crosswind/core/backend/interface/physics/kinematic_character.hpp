#pragma once

#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <glm/glm.hpp>

namespace cw{
namespace physics{

		class kinematic_character;

}// namespace physics
}// namespace cw

class cw::physics::kinematic_character{
public:
    kinematic_character(const glm::vec3& o,
                        const glm::vec2& size,
                        const float& step_height,
                        const glm::vec3& s,
                        const glm::vec3& u){

            scale = s;
            speed = glm::vec3(0.0f, 0.0f, 0.0f);

            unit_value= u;
            glm::vec3 s_origin = o * s;

            glm::vec2 s_size = size * glm::vec2(s.x, s.y);



            btTransform start_transform;
            start_transform.setIdentity ();
            start_transform.setOrigin (btVector3(s_origin.x, s_origin.y, s_origin.z));


            ghost_object = std::make_unique<btPairCachingGhostObject>();
            ghost_object->setWorldTransform(start_transform);

            capsule = std::make_unique<btCapsuleShape>(s_size.x/2, s_size.y/2);

            ghost_object->setCollisionShape (capsule.get());
            ghost_object->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);

            character_object = std::make_unique<btKinematicCharacterController> (ghost_object.get(), capsule.get(), step_height);

    }

    glm::vec3 get_origin(){
        btVector3 t;
        t = ghost_object->getWorldTransform().getOrigin();
        glm::vec3 origin(t[0], t[1], t[2]);
        origin/=scale;
        return origin;
    }

    void set_origin(const glm::vec3 origin){
        glm::vec3 s_origin = origin;
        s_origin *=  scale;

        btTransform t;
        t.setOrigin(btVector3(s_origin.x, s_origin.y, s_origin.z));

        ghost_object->setWorldTransform(t);
    }

    void set_jump_speed(const float spd){
        character_object->setJumpSpeed(spd*unit_value.y);
    }

    void jump(){
        character_object->jump();
    }

    void set_speed(const glm::vec3& spd){
        speed = spd;
        speed *= scale;
        character_object->setWalkDirection(btVector3(speed.x, speed.y, speed.z));
    }

    glm::vec3 get_speed(){
       return speed/scale;
    }

    bool on_ground(){
        return character_object->onGround();
    }

    void add_collision_test(std::function<void(void)> function){
  //      on_collision += function;
    }

//
 //   functional::delegate<void, void> on_collision;

public:
    std::unique_ptr<btKinematicCharacterController> character_object;
    std::unique_ptr<btPairCachingGhostObject> ghost_object;
    std::unique_ptr<btConvexShape> capsule;

private:
    glm::vec3 scale;
    glm::vec3 speed;
    glm::vec3 unit_value;

};// class kinematic_character