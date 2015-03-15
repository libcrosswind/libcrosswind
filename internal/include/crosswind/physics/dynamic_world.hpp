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
	dynamic_world(const glm::vec3& g){

        collision_config.reset(new btDefaultCollisionConfiguration());
        dispatcher.reset(new btCollisionDispatcher(collision_config.get()));
        broadphase.reset(new btDbvtBroadphase());
        solver.reset(new btSequentialImpulseConstraintSolver());
        world.reset(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collision_config.get()));
		physics_debug_drawer.reset(new debug::physics_debug_drawer());
		set_gravity(g);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		world->setDebugDrawer(physics_debug_drawer.get());

	}

	void set_scale(const glm::vec3& new_scale){
		scale = new_scale;
	}

	template<typename T, typename... Args>
	std::shared_ptr<detail::rigid_body> create(Args... args){
		return std::make_shared<T>(args..., scale);
	}

	void add_rigid_body(std::shared_ptr<detail::rigid_body> body){

		world->addRigidBody(body->physic_body.get());

	}

	void remove_rigid_body(std::shared_ptr<detail::rigid_body> body){
		world->removeCollisionObject(body->physic_body.get());
	}

	void set_gravity(const glm::vec3& g){
		glm::vec3 gravity = g*scale;
		world->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
	}

	void init_debug_drawer(auto camera){
		physics_debug_drawer->init(camera, scale);
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
	glm::vec3 scale;

};// class dynamic_world