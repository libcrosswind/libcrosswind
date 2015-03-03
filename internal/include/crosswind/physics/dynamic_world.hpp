#pragma once

#include <memory>
#include <btBulletDynamicsCommon.h>

#include <crosswind/math/vector3.hpp>

namespace cw{
namespace physics{

	class dynamic_world;
	class rigid_body;

}// namespace physics
}// namespace cw

class cw::physics::rigid_body{
	protected:
		rigid_body(	const cw::math::vector3& transform, 
					const bt::RigidBody::btRigidBodyConstructionInfo& info): 
		body(new btRigidBody(info)){

			transform.setIdentity();
			transform.setOrigin(btVector3(0, 0, 0));

		}

		virtual void init() = 0;

	protected:
		btTransform transform;
		std::unique_ptr<btRigidBody> body;
};

class cw::physics::static_plane: public cw::physics::rigid_body{
	public:
		static_plane(const cw::math::vector3& origin): rigid_body(origin){

			init();

//			 = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

		}

	protected:
		virtual void init(){

		}

		std::unique_ptr<btStaticPlaneShape> plane;
};

class cw::physics::dynamic_world{
public:
	dynamic_world(const cw::math::vector3 gravity):
	collision_config(new btDefaultCollisionConfiguration()), 
	dispatcher(new btDispatcher(collision_config.get()),
	broadphase(new btDbvtBroadphase()),
	solver(new btSequentialImpulseConstraintSolver()),
	world(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collision_config.get()){

		world->setGravity(gravity);

	}

	void add_rigid_body(std::shared_ptr<rigid_body> body){

		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(0, 0, 0));
		btMotionState* motion_state = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo info(0.0, motion_state, plane);
		world->addRigidBody(body);

	}

	void remove_rigid_body(btRigidBody* body){
		world->removeCollisionObject();
	}

	void set_gravity(const btVector3& gravity){
		world->setGravity(gravity);
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

};