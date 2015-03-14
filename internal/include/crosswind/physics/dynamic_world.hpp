#pragma once

#include <memory>

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <crosswind/physics/detail/rigid_body.hpp>

#include <crosswind/physics/debug/physics_debug_drawer.hpp>

namespace cw{
namespace physics{

	class dynamic_world;

}// namespace physics
}// namespace cw



class cw::physics::dynamic_world{
public:
	dynamic_world(const glm::vec3& gravity){

        collision_config.reset(new btDefaultCollisionConfiguration());
        dispatcher.reset(new btCollisionDispatcher(collision_config.get()));
        broadphase.reset(new btDbvtBroadphase());
        solver.reset(new btSequentialImpulseConstraintSolver());
        world.reset(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collision_config.get()));
		physics_debug_drawer.reset(new debug::physics_debug_drawer());
		set_gravity(gravity);

		world->setDebugDrawer(physics_debug_drawer.get());

	}

	void add_rigid_body(std::shared_ptr<detail::rigid_body> body){

		world->addRigidBody(body->physic_body.get());

	}

	void remove_rigid_body(std::shared_ptr<detail::rigid_body> body){
		world->removeCollisionObject(body->physic_body.get());
	}

	void set_gravity(const glm::vec3& gravity){
		world->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
	}

	void init_debug_drawer(auto camera){
		drawer->init(camera);
	}

	void debug_draw_world(){
		world->debugDrawWorld();
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
	std::unique_ptr<debug::physics_debug_drawer> physics_debug_drawer;


};// class dynamic_world