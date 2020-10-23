#include <terra.hpp>

#include <filesystem>

#include "crosswind/composition/tilemap.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/graphical/video.hpp"

#include "crosswind/graphical/opengl/texture.hpp"
#include "crosswind/graphical/opengl/renderer.hpp"
#include "crosswind/graphical/opengl/debug_renderer.hpp"

#include "crosswind/graphical/object/sprite.hpp"

#include "crosswind/simulation/detail/body.hpp"
#include "crosswind/simulation/detail/character.hpp"

#include "crosswind/platform/input.hpp"

#include "crosswind/simulation/physics.hpp"

#include "title.hpp"

typedef std::map<std::string, std::vector<std::pair<glm::vec3, glm::vec3> > > actor_collision_map;
typedef std::map<std::string, actor_collision_map> scene_collision_map;

game::characters::title::terra::terra(std::shared_ptr<cw::composition::core> core, 
									  std::shared_ptr<game::scenes::title> title,
									  const std::string& path) :
	sprite_set(core, path),
	physical(core, "terra"){
	current_sprite = sprites.at(0);
	animation_time = 0.0f;

	this->title = title;
	this->core = core;

	for (auto sprite : sprites) {
		sprite->set_origin(glm::vec3(312, 224, 0));
	}


	bbox = cw::geometry::rectangle(glm::ivec2(312 - 40 * 0.5f, 224 - 42 * 0.5f), glm::ivec2(40, 42));

	/*this->add_rigid_body("terra", 
						 glm::vec3(312, -224, 0),
						 glm::vec3(40.0f, 42.0f, 10.0f),
						 0.0f);*/
}

std::string game::characters::title::terra::get_collision_map(const std::string& actor_a) {

	if (collisions.find(actor_a) != collisions.end()) {
		return collisions[actor_a];
	}
	else {
		return collisions["undefined"];
	}

}

void game::characters::title::terra::find_collisions() {

	can_move_left = true;
	can_move_right = true;
	can_move_up = true;
	can_move_down = true;

	for (auto wall : title->walls) {
		if (wall->bbox.intersects(bbox)) {
			if (wall->bbox.centre().x > bbox.centre().x) {
				can_move_right = false;
			}

			if (wall->bbox.centre().x < bbox.centre().x) {
				can_move_left = false;
			}

			if (wall->bbox.centre().y > bbox.centre().y) {
				can_move_up = false;
			}

			if (wall->bbox.centre().y < bbox.centre().y) {
				can_move_down = false;
			}
			collisions["terra"] = "wall";
		}
	}

	/*int numManifolds = core->physics->get_collision_manifolds_number();
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
	}*/
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

	/*auto character = this->get_rigid_body("terra");
	glm::vec3 b_origin(character->get_origin().x,
					   character->get_origin().y,
					   character->get_origin().z);*/
	find_collisions();


	if (core->input->is_key_down("Right") && can_move_right) {
		glm::vec3 origin = glm::vec3(this->current_sprite->get_origin());

		auto speed = glm::vec3(origin.x + 8, origin.y, origin.z);

		for (auto sprite : sprites) {
			sprite->set_origin(speed);
		}

		/*core->physics->remove_rigid_body(character);
		character->set_origin(speed);
		core->physics->add_rigid_body(character);*/

		bbox.X += 8;
	}
	if (core->input->is_key_down("Left") && can_move_left) {
		glm::vec3 origin = glm::vec3(this->current_sprite->get_origin());

		auto speed = glm::vec3(origin.x - 8, origin.y, origin.z);

		for (auto sprite : sprites) {
			sprite->set_origin(speed);
		}

		bbox.X -= 8;
	}

	if (core->input->is_key_down("Up") && can_move_up) {
		glm::vec3 origin = glm::vec3(this->current_sprite->get_origin());

		auto speed = glm::vec3(origin.x, origin.y + 8, origin.z);

		for (auto sprite : sprites) {
			sprite->set_origin(speed);
		}

		bbox.Y += 8;
	}

	if (core->input->is_key_down("Down") && can_move_down) {
		glm::vec3 origin = glm::vec3(this->current_sprite->get_origin());

		auto speed = glm::vec3(origin.x, origin.y - 8, origin.z);

		for (auto sprite : sprites) {
			sprite->set_origin(speed);
		}

		bbox.Y -= 8;
	}

}



void game::characters::title::terra::draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) {

	renderer->upload(current_sprite);
	renderer->debug_renderer->debug_draw(glm::vec4(bbox.X, bbox.Y, bbox.Width, bbox.Height));
}