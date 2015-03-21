#pragma once

#include <memory>

#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

#include <crosswind/physics/detail/rigid_body.hpp>
#include <crosswind/physics/kinematic_character.hpp>

#include <crosswind/physics/debug/physics_debug_drawer.hpp>
#include <crosswind/physics/box.hpp>

namespace cw{
namespace physics{

	class dynamic_world;

}// namespace physics
}// namespace cw



class cw::physics::dynamic_world{
public:
	dynamic_world(const glm::vec3& g, const glm::vec3& s, const glm::vec3& u): scale(s), unit_value(u){

		btVector3 world_min(-1000,-1000,-1000);
		btVector3 world_max(1000,1000,1000);
		btAxisSweep3* sweepBP = new btAxisSweep3(world_min,world_max);


		collision_config.reset(new btDefaultCollisionConfiguration());
        dispatcher.reset(new btCollisionDispatcher(collision_config.get()));
        broadphase.reset(new btAxisSweep3(world_min, world_max));
        solver.reset(new btSequentialImpulseConstraintSolver());
        world.reset(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collision_config.get()));
		physics_debug_drawer.reset(new debug::physics_debug_drawer());

		scale *= u;
		set_gravity(g);

		world->setDebugDrawer(physics_debug_drawer.get());

		world->getDispatchInfo().m_allowedCcdPenetration=0.0001f;
	    broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());


	}

	void set_scale(const glm::vec3& new_scale){
		scale = new_scale;
	}

	void set_gravity(const glm::vec3& g){
		glm::vec3 gravity = g * scale;
		std::cout << scale.x << " " << scale.y << " " << scale.z << std::endl;
		world->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
	}

	void init_debug_drawer(auto camera){
		physics_debug_drawer->init(camera, scale);
	}


	template<typename T, typename... Args>
	std::shared_ptr<detail::rigid_body> create(Args... args){
		return std::make_shared<T>(args..., scale);
	}

	template<typename T>
	auto create_rigid_body(const glm::vec3& origin, const glm::vec3& size, const float& mass){
		return std::make_shared<T>(origin, size, mass, scale, unit_value);
	}

	auto create_character(const glm::vec3& origin, const glm::vec2& size, const float& step_height){
		return std::make_shared<kinematic_character>(origin, size, step_height, scale, unit_value);
	}

	void add_rigid_body(std::shared_ptr<detail::rigid_body> body){

		auto st = body->physic_body->getLinearSleepingThreshold();

		st *= (scale.x +scale.y + scale.z / 3.0f);

		body->physic_body->setSleepingThresholds(st, body->physic_body->getAngularSleepingThreshold());

		world->addRigidBody(body->physic_body.get());

	}

	void remove_rigid_body(std::shared_ptr<detail::rigid_body> body){
		world->removeRigidBody(body->physic_body.get());
	}

	void add_character(std::shared_ptr<kinematic_character> character){

		world->addCollisionObject(character->ghost_object.get(),
				                  btBroadphaseProxy::CharacterFilter,
				                  btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

		world->addAction(character->character_object.get());
	}

	void remove_character(std::shared_ptr<kinematic_character> character){

		world->removeAction(character->character_object.get());
		world->removeCollisionObject(character->ghost_object.get());

	}


	void contact_test(std::shared_ptr<detail::rigid_body> body, btCollisionWorld::ContactResultCallback& resultCallback){
		world->contactTest(body->physic_body.get(), resultCallback);
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
	glm::vec3 unit_value;

};// class dynamic_world