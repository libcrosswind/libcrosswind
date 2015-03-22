#pragma once


#include <btBulletDynamicsCommon.h>

#include <crosswind/interface/simulation/physics.hpp>
#include <crosswind/implementation/simulation/detail/character.hpp>
#include <crosswind/implementation/simulation/detail/body.hpp>


namespace cw{
namespace implementation{
namespace simulation{

	class physics;

}// namespace simulation
}// namespace implementation
}// namespace cw

class cw::implementation::simulation::physics: public cw::interface::simulation::physics{
public:
	physics(const glm::vec3& c_gravity,
			const glm::vec3& c_scale,
			const glm::vec3& c_unit_value):
		cw::interface::simulation::physics(c_gravity, c_scale, c_unit_value){

		btVector3 world_min(-1000,-1000,-1000);
		btVector3 world_max(1000,1000,1000);
		btAxisSweep3* sweepBP = new btAxisSweep3(world_min,world_max);

		btDefaultCollisionConstructionInfo construction_info = btDefaultCollisionConstructionInfo();
		construction_info.m_defaultMaxCollisionAlgorithmPoolSize = 1024;
		construction_info.m_defaultMaxPersistentManifoldPoolSize = 1024;

		collision_config.reset(new btDefaultCollisionConfiguration(construction_info));

		dispatcher.reset(new btCollisionDispatcher(collision_config.get()));
		broad_phase.reset(new btAxisSweep3(world_min, world_max));
        solver.reset(new btSequentialImpulseConstraintSolver());
        world.reset(new btDiscreteDynamicsWorld(dispatcher.get(), broad_phase.get(), solver.get(), collision_config.get()));
//		physics_debug_drawer.reset(new debug::physics_debug_drawer());

		scale *= unit_value;
		set_gravity(c_gravity);

//		world->setDebugDrawer(physics_debug_drawer.get());

		world->getDispatchInfo().m_allowedCcdPenetration=0.0001f;
		broad_phase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());


	}

	virtual void set_scale(const glm::vec3& new_scale){
		scale = new_scale;
	}

	virtual glm::vec3 get_scale(){
		return scale;
	}

	virtual void set_gravity(const glm::vec3& new_gravity){
		gravity = new_gravity * scale;
		world->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
	}

	virtual glm::vec3 get_gravity(){
		return gravity/scale;
	}

	virtual void debug_draw_world(const glm::mat4& projection_matrix){
		world->debugDrawWorld();
	}

	virtual void update(float dt){
		world->stepSimulation(dt);
	}

	template<typename T>
	auto create_character(const glm::vec3& origin, const glm::vec2& size, const float& step_height){
		auto character = std::make_shared<T>(origin, size, step_height);
		add_character(character);
		return character;
	}

	virtual void add_character(std::shared_ptr<interface::simulation::detail::character> character_ptr){
		auto character = std::dynamic_pointer_cast<detail::character>(character_ptr);
		world->addCollisionObject(character->ghost_object.get(),
				btBroadphaseProxy::CharacterFilter,
				btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

		world->addAction(character->character_object.get());
	}

	virtual void remove_character(std::shared_ptr<interface::simulation::detail::character> character_ptr){
		auto character = std::dynamic_pointer_cast<detail::character>(character_ptr);
		world->removeAction(character->character_object.get());
		world->removeCollisionObject(character->ghost_object.get());
	}

	template<typename T>
	auto create_body(const glm::vec3& origin, const glm::vec3& size, const float& mass){
		auto body = std::make_shared<T>(origin, size, mass, scale, unit_value);
		add_rigid_body(body);
		return body;
	}

	virtual void add_body(std::shared_ptr<interface::simulation::detail::body> body_ptr){
		auto body = std::dynamic_pointer_cast<detail::body>(body_ptr);
		auto st = body->physic_body->getLinearSleepingThreshold();
		st *= (scale.x +scale.y + scale.z / 3.0f);
		body->physic_body->setSleepingThresholds(st, body->physic_body->getAngularSleepingThreshold());
		world->addRigidBody(body->physic_body.get());
	}

	virtual void remove_body(std::shared_ptr<interface::simulation::detail::body> body_ptr){
		auto body = std::dynamic_pointer_cast<detail::body>(body_ptr);
		world->removeRigidBody(body->physic_body.get());
	}

private:
	std::unique_ptr<btDynamicsWorld> 			world;
	std::unique_ptr<btConstraintSolver> 		solver;
	std::unique_ptr<btBroadphaseInterface> 		broad_phase;
	std::unique_ptr<btDispatcher>    			dispatcher;
	std::unique_ptr<btCollisionConfiguration>	collision_config;
//	std::unique_ptr<debug::physics_debug_drawer> physics_debug_drawer;

};// class dynamic_world