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

	protected:
		rigid_body(const glm::vec3& origin){

			transform.setIdentity();
			transform.setOrigin(btVector3(origin.x, origin.y, origin.z));

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

public:
        glm::vec3 get_origin(){
            btVector3 t;
			t = physic_body->getCenterOfMassPosition();
            return glm::vec3(t[0], t[1], t[2]);
        }

        btTransform transform;
		std::unique_ptr<btMotionState> motion_state;
		std::unique_ptr<btCollisionShape> collision_shape;
		std::unique_ptr<btRigidBody> physic_body;

};// class rigid_body