#include <stdexcept>

#include "crosswind/simulation/physics.hpp"
#include "crosswind/simulation/detail/character.hpp"
#include "crosswind/simulation/detail/body.hpp"
#include "crosswind/simulation/box.hpp"
#include "crosswind/simulation/debug/opengl/drawer.hpp"

cw::simulation::physics::physics(const glm::vec3& c_gravity,
										  	     const glm::vec3& c_scale,
										  		 const glm::vec3& c_unit_value):
gravity(c_gravity),
scale(c_scale),
unit_value(c_unit_value){

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
	drawer.reset(new class debug::opengl::drawer());

	scale.x *= unit_value.x;
	scale.y *= unit_value.y;
	scale.z *= unit_value.z;

	set_gravity(c_gravity);

	world->setDebugDrawer(drawer.get());

	world->getDispatchInfo().m_allowedCcdPenetration=0.0001f;
	broad_phase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());


}

void cw::simulation::physics::set_scale(const glm::vec3& new_scale){
	
	scale = new_scale;

}

glm::vec3 cw::simulation::physics::get_scale(){
	
	return scale;

}

void cw::simulation::physics::set_gravity(const glm::vec3& new_gravity){
	
	gravity = new_gravity * scale;
	world->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

}

glm::vec3 cw::simulation::physics::get_gravity(){
	
	return gravity/scale;

}

void cw::simulation::physics::debug_draw_world(const glm::mat4& projection_matrix){
	
	physics_debug_drawer->update(projection_matrix, scale);
	world->debugDrawWorld();

}

void cw::simulation::physics::update(float dt){
	
	world->stepSimulation(dt);

}

auto cw::simulation::physics::create_character(const glm::vec3& origin, 
															   const glm::vec2& size, 
															   const float& step_height){

	auto character = std::make_shared<detail::character>(origin, size, scale, unit_value, step_height);
	add_character(character);
	return character;

}

void cw::simulation::physics::add_character(std::shared_ptr<detail::character> character_ptr){

	auto character = std::dynamic_pointer_cast<detail::character>(character_ptr);
	world->addCollisionObject(character->ghost_object.get(),
			btBroadphaseProxy::CharacterFilter,
			btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);

	world->addAction(character->character_object.get());

}

void cw::simulation::physics::remove_character(std::shared_ptr<detail::character> character_ptr){

	auto character = std::dynamic_pointer_cast<detail::character>(character_ptr);
	world->removeAction(character->character_object.get());
	world->removeCollisionObject(character->ghost_object.get());

}

auto cw::simulation::physics::create_primitive(const PRIMITIVE_PROXY& proxy_type,
											   const glm::vec3& origin,
											   const glm::vec3& size,
											   const float& mass){

	std::shared_ptr<detail::body> body;

	switch(proxy_type){

		case PRIMITIVE_PROXY::BOX:
			body = std::make_shared<box>(origin, size, mass, scale, unit_value);
		break;

		case PRIMITIVE_PROXY::SPHERE:
//				body = std::make_shared<box>(origin, size, mass, scale, unit_value);
		break;

		case PRIMITIVE_PROXY::PLANE:
//				body = std::make_shared<box>(origin, size, mass, scale, unit_value);
		break;

		default:
			throw std::runtime_error("No proxy type specified");

	}

	add_rigid_body(body);

	return body;

}


void cw::simulation::physics::add_rigid_body(std::shared_ptr<detail::body> body_ptr){

	auto body = std::dynamic_pointer_cast<detail::body>(body_ptr);
	auto st = body->physic_body->getLinearSleepingThreshold();
	st *= (scale.x +scale.y + scale.z / 3.0f);
	body->physic_body->setSleepingThresholds(st, body->physic_body->getAngularSleepingThreshold());
	world->addRigidBody(body->physic_body.get());

}

void cw::simulation::physics::remove_rigid_body(std::shared_ptr<detail::body> body_ptr){

	auto body = std::dynamic_pointer_cast<detail::body>(body_ptr);
	world->removeRigidBody(body->physic_body.get());

}

int cw::simulation::physics::get_collision_manifolds_number(){
	
	return dispatcher->getNumManifolds();

}

btPersistentManifold* cw::simulation::physics::get_manifold_by_index(const int& index){

	return dispatcher->getManifoldByIndexInternal(index);

} 