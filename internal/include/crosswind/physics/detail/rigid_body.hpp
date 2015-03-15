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

class cw::physics::detail::rigid_body{

public:
		rigid_body(const glm::vec3& o, const glm::vec3& s = glm::vec3(1.0f, 1.0f, 1.0f)): scale(s){

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

		void apply_force(const glm::vec3& f){

			glm::vec3 force = f*scale;
			physic_body->activate(true);
			physic_body->applyCentralImpulse( btVector3( force.x, force.y, force.z ) );
		}

        btTransform transform;
		glm::vec3 scale;

		std::unique_ptr<btMotionState> motion_state;
		std::unique_ptr<btCollisionShape> collision_shape;
		std::unique_ptr<btRigidBody> physic_body;


};// class rigid_body