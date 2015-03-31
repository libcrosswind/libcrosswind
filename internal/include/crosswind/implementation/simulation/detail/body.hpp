#pragma once

#include <memory>

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <crosswind/interface/simulation/detail/body.hpp>

namespace cw{
namespace implementation{
namespace simulation{
namespace detail{

	class body;

}// namespace detail
}// namespace simulation
}// namespace implementation
}// namespace cw


class cw::implementation::simulation::detail::body: public cw::interface::simulation::detail::body{

public:
	body(const glm::vec3& c_origin, 
		 const glm::vec3& c_scale      = glm::vec3(1.0f, 1.0f, 1.0f), 
		 const glm::vec3& c_unit_value = glm::vec3(1.0f, 1.0f, 1.0f)):
	interface::simulation::detail::body(c_origin, c_scale, c_unit_value){

			origin *= scale;

	}

	void init(const float& mass, btMotionState* state, btCollisionShape* shape){

        btScalar m(mass);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (m != 0.f);

        btVector3 localInertia(0,0,0);
        if (isDynamic)
            shape->calculateLocalInertia(m,localInertia);


        btRigidBody::btRigidBodyConstructionInfo info(m, state, shape, localInertia);

		motion_state 	= std::unique_ptr<btMotionState>(state);
		collision_shape = std::unique_ptr<btCollisionShape>(shape);
		physic_body		= std::make_unique<btRigidBody>(info);
	}

	void set_activation_policy(int policy){
		physic_body->setActivationState(policy);
	}

    virtual void set_origin(const glm::vec3& new_origin){
		origin = new_origin;
		origin *=  scale;

		btTransform transform;
		transform.setOrigin(btVector3(origin.x, origin.y, origin.z));

		physic_body->setCenterOfMassTransform(transform);

    }
	virtual glm::vec3 get_origin(){
        btVector3 t;
		t = physic_body->getCenterOfMassPosition();
		glm::vec3 origin(t[0], t[1], t[2]);
		origin/=scale;
        return origin;
	}

	virtual void set_linear_speed(const glm::vec3& speed){
		auto spd = speed * scale;
		spd /= unit_value;
		physic_body->setLinearVelocity(btVector3(spd.x, spd.y, spd.z));

	}

	virtual glm::vec3 get_linear_speed(){

		glm::vec3 spd(physic_body->getLinearVelocity().getX(),
		physic_body->getLinearVelocity().getY(),
		physic_body->getLinearVelocity().getZ());
		return spd / scale * unit_value;

	}

	virtual void apply_force(const glm::vec3& new_force){
		glm::vec3 force = new_force*scale;
		physic_body->activate(true);
		physic_body->applyCentralImpulse( btVector3( force.x, force.y, force.z ) );
	}


	void set_linear_factor(const glm::vec3& position, const glm::vec3& rotation){

		physic_body->setLinearFactor(btVector3(position.x, position.y, position.z));
		physic_body->setAngularFactor(btVector3(rotation.x, rotation.y, rotation.z));

	}

};// class body