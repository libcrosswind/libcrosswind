#pragma once

#include <memory>

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

namespace cw{
namespace physics{
namespace detail{

	class rigid_body;

}// namespace detail
}// namespace physics
}// namespace cw

#include <iostream>


struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback {

	//! Constructor, pass whatever context you want to have available when processing contacts
	/*! You may also want to set m_collisionFilterGroup and m_collisionFilterMask
	 *  (supplied by the superclass) for needsCollision() */
	ContactSensorCallback(btRigidBody* tgtBody /* , YourContext& context*/ /*, ... */)
			: btCollisionWorld::ContactResultCallback(), body(tgtBody)/*, ctxt(context)*/ {

		scale = 0.01f;
	}

	btRigidBody* body; //!< The body the sensor is monitoring
	//YourContext& ctxt; //!< External information for contact processing

	//! If you don't want to consider collisions where the bodies are joined by a constraint, override needsCollision:
	/*! However, if you use a btCollisionObject for #body instead of a btRigidBody,
	 *  then this is unnecessary—checkCollideWithOverride isn't available */
	virtual bool needsCollision(btBroadphaseProxy* proxy) const {
		// superclass will check m_collisionFilterGroup and m_collisionFilterMask
		if(!btCollisionWorld::ContactResultCallback::needsCollision(proxy))
			return false;
		// if passed filters, may also want to avoid contacts between constraints
		return body->checkCollideWithOverride(static_cast<btCollisionObject*>(proxy->m_clientObject));
	}

	//! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
	virtual btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0,int partId0,int index0,
			const btCollisionObjectWrapper* colObj1,int partId1,int index1)
	{
		btVector3 pt; // will be set to point of collision relative to body
		if(colObj0->m_collisionObject==body) {
			pt = cp.m_localPointA;
		} else {
			assert(colObj1->m_collisionObject==body && "body does not match either collision object");
			pt = cp.m_localPointB;
		}

		std::cout << "Collision X: " << pt.getX() / scale << " Y: " << pt.getY() / scale << " Z: " << pt.getZ() / scale << std::endl;
		// do stuff with the collision point
		return 0; // There was a planned purpose for the return value of addSingleResult, but it is not used so you can ignore it.
	}

	float scale;


};

class cw::physics::detail::rigid_body{

public:
		rigid_body(const glm::vec3& o, const glm::vec3& s = glm::vec3(1.0f, 1.0f,1.0f), const glm::vec3& u = glm::vec3(1,1,1)): scale(s), unit_value(u){

			glm::vec3 s_origin = o * s;

			transform.setIdentity();
			transform.setOrigin(btVector3(s_origin.x, s_origin.y, s_origin.z));

		}

		void init(const float& mass, btMotionState* m_state, btCollisionShape* c_shape){

            btScalar m(mass);

            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            bool isDynamic = (m != 0.f);

            btVector3 localInertia(0,0,0);
            if (isDynamic)
                c_shape->calculateLocalInertia(m,localInertia);


            btRigidBody::btRigidBodyConstructionInfo info(m, m_state, c_shape, localInertia);

			motion_state 	= std::unique_ptr<btMotionState>(m_state);
			collision_shape = std::unique_ptr<btCollisionShape>(c_shape);
			physic_body		= std::make_unique<btRigidBody>(info);
		}

		void set_activation_policy(auto state){
			physic_body->setActivationState(state);
		}

        glm::vec3 get_origin(){
            btVector3 t;
			t = physic_body->getCenterOfMassPosition();
			glm::vec3 origin(t[0], t[1], t[2]);
			origin/=scale;
            return origin;
        }

        void set_origin(const glm::vec3 origin){
			glm::vec3 s_origin = origin;
			s_origin *=  scale;

			btTransform t;
			t.setOrigin(btVector3(s_origin.x, s_origin.y, s_origin.z));

//			physic_body->translate(btVector3(s_origin.x, s_origin.y, s_origin.z));
			physic_body->setCenterOfMassTransform(t);
        }

		void set_linear_factor(const glm::vec3& position, const glm::vec3& rotation){

			physic_body->setLinearFactor(btVector3(position.x, position.y, position.z));
			physic_body->setAngularFactor(btVector3(rotation.x, rotation.y, rotation.z));

		}

		void set_linear_speed(const glm::vec3& speed){

			auto spd = speed * scale;
			spd /= unit_value;
			physic_body->setLinearVelocity(btVector3(spd.x, spd.y, spd.z));

		}

		glm::vec3 get_linear_speed(){
			glm::vec3 spd(physic_body->getLinearVelocity().getX(),
						  physic_body->getLinearVelocity().getY(),
						  physic_body->getLinearVelocity().getZ());
			return spd / scale * unit_value;
		}

		void apply_force(const glm::vec3& f){

			glm::vec3 force = f*scale;
			physic_body->activate(true);
			physic_body->applyCentralImpulse( btVector3( force.x, force.y, force.z ) );
		}

        btTransform transform;
	    glm::vec3 scale;
	    glm::vec3 unit_value;

		std::unique_ptr<btMotionState> motion_state;
		std::unique_ptr<btCollisionShape> collision_shape;
		std::unique_ptr<btRigidBody> physic_body;


};// class rigid_body