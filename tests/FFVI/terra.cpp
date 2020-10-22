#include <terra.hpp>

#include <filesystem>

#include "crosswind/composition/tilemap.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/graphical/video.hpp"

#include "crosswind/graphical/opengl/texture.hpp"
#include "crosswind/graphical/opengl/renderer.hpp"

#include "crosswind/graphical/object/sprite.hpp"

#include "crosswind/simulation/detail/body.hpp"
#include "crosswind/simulation/detail/character.hpp"

#include "crosswind/platform/input.hpp"

#include "crosswind/simulation/physics.hpp"

typedef std::map<std::string, std::vector<std::pair<glm::vec3, glm::vec3> > > actor_collision_map;
typedef std::map<std::string, actor_collision_map> scene_collision_map;

game::characters::title::terra::terra(std::shared_ptr<cw::composition::core> core, const std::string& path) :
	sprite_set(core, path),
	physical(core, "terra"){
	current_sprite = sprites.at(0);
	animation_time = 0.0f;

	this->core = core;

	for (auto sprite : sprites) {
		sprite->set_origin(glm::vec3(1024 / 2.0f, -768 / 2.0f, 0));
	}

	this->add_rigid_body("terra", 
						 glm::vec3(312, -224, 0),
						 glm::vec3(40.0f, 42.0f, 10.0f),
						 0.0f);
}

actor_collision_map& game::characters::title::terra::get_collision_map(const std::string& actor_a) {

	if (collisions.find(actor_a) != collisions.end()) {
		return collisions[actor_a];
	}
	else {
		return collisions["undefined"];
	}

}

void game::characters::title::terra::find_collisions() {

	int numManifolds = core->physics->get_collision_manifolds_number();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = core->physics->get_manifold_by_index(i);

		int num_contacts = contactManifold->getNumContacts();
		if (num_contacts) {

			const btCollisionObject* obA = contactManifold->getBody0();
			const btCollisionObject* obB = contactManifold->getBody1();


			auto& a_name = static_cast<physical*>(obA->getUserPointer())->name;
			auto& b_name = static_cast<physical*>(obB->getUserPointer())->name;

			for (int j = 0; j < num_contacts; j++) {
				btManifoldPoint& contact = contactManifold->getContactPoint(j);

				glm::vec3 a(contact.m_localPointA.x(), contact.m_localPointA.y(), contact.m_localPointA.z());
				glm::vec3 b(contact.m_localPointB.x(), contact.m_localPointB.y(), contact.m_localPointB.z());

				collisions[a_name][b_name].push_back(std::make_pair(a, b));

			}
		}
	}
}

void game::characters::title::terra::logic(const float& delta) {
	animation_time += delta;

	if (animation_time >= 0.0625f) {
		animation_time = 0.0f;

		sprite_index++;

		if (sprite_index == 6) {
			sprite_index = 0;
		}

		if (sprite_index >= sprites.size()) {
			sprite_index = 0;
		}

		current_sprite = sprites.at(sprite_index);
	}

	auto character = this->get_rigid_body("terra");
	glm::vec3 b_origin(character->get_origin().x,
					   character->get_origin().y,
					   character->get_origin().z);

	this->current_sprite->set_origin(b_origin);

	if (core->input->is_key_down("Right")) {
		auto speed = glm::vec3(b_origin.x + 8, b_origin.y, b_origin.z);

		core->physics->remove_rigid_body(character);
		character->set_origin(speed);
		core->physics->add_rigid_body(character);
	}
	if (core->input->is_key_down("Left")) {
		auto speed = glm::vec3(b_origin.x - 8, b_origin.y, b_origin.z);
		character->set_origin(speed);
	}

	find_collisions();

	auto& collision_map = get_collision_map("terra");
	if (!collision_map.empty()) {
		if (collision_map.find("wall") != collision_map.end()) {
			auto speed = glm::vec3(0, 0, 0);
			//character->set_speed(speed);

		}
	}
}



void game::characters::title::terra::draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) {

	renderer->upload(current_sprite);
}