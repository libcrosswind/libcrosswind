/*#include <filesystem>
#include <algorithm>
#include <vector>

#include "crosswind/composition/physical.hpp"

#include "crosswind/composition/core.hpp"

#include "crosswind/simulation/physics.hpp"

#include "crosswind/simulation/detail/body.hpp"

#include "crosswind/simulation/detail/character.hpp"


cw::composition::physical::physical(std::shared_ptr<cw::composition::core> core,
									const std::string& name) :
    core(core), name(name) {

}

cw::composition::physical::~physical()
{
	for (auto& body_mapping : bodies) {
		core->physics->remove_rigid_body(body_mapping.second);
	}

	for (auto& character_mapping : characters) {
		core->physics->remove_character(character_mapping.second);
	}

}


void cw::composition::physical::add_rigid_body(const std::string& body_name,
											   const glm::vec3& origin,
											   const glm::vec3& size,
											   const float& mass) {

	if (bodies.find(body_name) == bodies.end()) {
		bodies[body_name] = core->physics->create_primitive(simulation::physics::PRIMITIVE_PROXY::BOX,
			origin,
			size,
			mass);

		bodies[body_name]->physic_body->setUserPointer(this);

	}
	else {
		throw std::runtime_error(body_name + " already exists, remove it first before adding one with the same name");
	}

}

std::shared_ptr<cw::simulation::detail::body> 
cw::composition::physical::get_rigid_body(const std::string& body_name) {

	if (bodies.find(body_name) != bodies.end()) {
		return bodies[body_name];
	}
	else {
		throw std::runtime_error(body_name + " does not exist");
	}

}

void cw::composition::physical::remove_rigid_body(const std::string& body_name) {

	if (bodies.find(body_name) != bodies.end()) {
		core->physics->remove_rigid_body(bodies[body_name]);
		bodies.erase(body_name);
	}
	else {
		throw std::runtime_error(body_name + " does not exist or was already removed");
	}

}


void cw::composition::physical::add_character(const std::string& character_name,
												const glm::vec3& origin,
												const glm::vec2& size,
												const float& step_height) {

	if (characters.find(character_name) == characters.end()) {
		characters[character_name] = core->physics->create_character(origin, size, step_height);
		static_cast<btKinematicCharacterController*>(characters[character_name]->get_character_object())->
			getGhostObject()->setUserPointer(this);
	}
	else {
		throw std::runtime_error(character_name + " already exists, remove it first before adding one with the same name");
	}

}

std::shared_ptr<cw::simulation::detail::character> cw::composition::physical::get_character(const std::string& character_name) {

	if (characters.find(character_name) != characters.end()) {
		return characters[character_name];
	}
	else {
		throw std::runtime_error(character_name + " does not exist");
	}

}

void cw::composition::physical::remove_character(const std::string& character_name) {

	if (characters.find(character_name) != characters.end()) {
		core->physics->remove_character(characters[character_name]);
		characters.erase(character_name);
	}
	else {
		throw std::runtime_error(character_name + " does not exist or was already removed");
	}

}
*/