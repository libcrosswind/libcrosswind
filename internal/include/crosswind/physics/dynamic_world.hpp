#pragma once

#include <memory>
#include <btBulletDynamicsCommon.h>

#include <glm/glm.hpp>

namespace cw{
namespace physics{

	class dynamic_world;
	class rigid_body;
	class static_plane;
    class box;

}// namespace physics
}// namespace cw

#include <iostream>

class cw::physics::rigid_body{
	protected:
		rigid_body(const glm::vec3& origin){

            std::cout << "Origin: " << origin.x << " " << origin.y << " " << origin.z << std::endl;
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

        glm::vec3 get_position(){
            btTransform t;
            physic_body->getMotionState()->getWorldTransform(t);
            return glm::vec3(t.getOrigin().getX(), t.getOrigin().getY(), t.getOrigin().getZ());
        }

        btTransform transform;
		std::unique_ptr<btMotionState> motion_state;
		std::unique_ptr<btCollisionShape> collision_shape;
		std::unique_ptr<btRigidBody> physic_body;
};

class cw::physics::static_plane: public cw::physics::rigid_body{
	public:
		static_plane(const glm::vec3& origin,
                     const glm::vec3& size):
		rigid_body(origin){

			init(0.0f,
                 new btDefaultMotionState(transform),
				 new btStaticPlaneShape(btVector3(size.x, size.y, size.z),0));

		}

};


class cw::physics::box: public cw::physics::rigid_body{
public:
    box(const float& mass,
                 const glm::vec3& origin,
                 const glm::vec3& size):
            rigid_body(origin){

            init(mass,
                 new btDefaultMotionState(transform),
                 new btBoxShape(btVector3(size.x, size.y, size.z)));

    }

};


class cw::physics::dynamic_world{
public:
	dynamic_world(const glm::vec3& gravity){

        collision_config.reset(new btDefaultCollisionConfiguration());
        dispatcher.reset(new btCollisionDispatcher(collision_config.get()));
        broadphase.reset(new btDbvtBroadphase());
        solver.reset(new btSequentialImpulseConstraintSolver());
        world.reset(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collision_config.get()));
		set_gravity(gravity);
	
	}

	void add_rigid_body(std::shared_ptr<rigid_body> body){

		world->addRigidBody(body->physic_body.get());

	}

	void remove_rigid_body(std::shared_ptr<rigid_body> body){
		world->removeCollisionObject(body->physic_body.get());
	}

	void set_gravity(const glm::vec3& gravity){
		world->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
	}

	void update(double dt){
		world->stepSimulation(dt);
	}

private:
	std::unique_ptr<btDynamicsWorld> 			world;
	std::unique_ptr<btConstraintSolver> 		solver;
	std::unique_ptr<btBroadphaseInterface> 		broadphase;
	std::unique_ptr<btDispatcher>    			dispatcher;
	std::unique_ptr<btCollisionConfiguration>	collision_config;

};// class dynamic_world