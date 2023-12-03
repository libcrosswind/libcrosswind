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

#include "crosswind/engine.hpp"

#include "crosswind/composition/stage.hpp"

#include "crosswind/simulation/physics.hpp"

#include "gameplay.hpp"
#include "battle.hpp"


typedef std::map<std::string, std::vector<std::pair<glm::vec3, glm::vec3> > > actor_collision_map;
typedef std::map<std::string, actor_collision_map> scene_collision_map;

game::characters::terra::terra(std::shared_ptr<cw::composition::core> core, 
									  std::shared_ptr<game::scenes::gameplay> gameplay,
									  const std::string& path) :
	
	base(core, path)
	/*physical(core, "terra")*/{

	idle_right = true;
	idle_left = true;
	idle_up = true;
	idle_down = true;

	current_sprite = sprites.at(0);

	walking_direction_facing = walking_direction::down;

	sprite_index = 0;

	animations["down"].insert(animations["down"].begin(), sprites.begin(), sprites.begin() + 3);
	
	animations["up"].insert(animations["up"].begin(), sprites.begin() + 3, sprites.begin() + 6);
	
	animations["left"].insert(animations["left"].begin(), sprites.begin() + 6, sprites.begin() + 9);

	animations["right"].insert(animations["right"].begin(), sprites.begin() + 6, sprites.begin() + 9);

	animation_time = 0.0f;

	this->gameplay = gameplay;
	this->core = core;

	bbox.Width = 24;
	bbox.Height = 20;

	set_position(glm::ivec2(312, 224));

	battle_trigger = false;

	/*this->add_rigid_body("terra", 
						 glm::vec3(312, -224, 0),
						 glm::vec3(40.0f, 42.0f, 10.0f),
						 0.0f);*/
}

void game::characters::terra::set_position(const glm::vec2& new_position) {

	for (auto sprite : sprites) {
		sprite->set_origin(glm::vec3(new_position.x, new_position.y, -1));
	}

	auto sprite_size = current_sprite->get_size();

	auto bbox_new_x = new_position.x - bbox.Width * 0.5f;
	auto bbox_new_y = new_position.y - sprite_size.y * 0.5f;

	bbox.X = bbox_new_x;
	bbox.Y = bbox_new_y;

	position = new_position;
}

glm::vec2 game::characters::terra::get_position() {
	return position;
}

std::string game::characters::terra::get_collision_map(const std::string& actor_a) {

	if (collisions.find(actor_a) != collisions.end()) {
		return collisions[actor_a];
	} else {
		return collisions["undefined"];
	}

}

void game::characters::terra::find_collisions() {

	if (gameplay == nullptr) {
		return;
	}

	for (auto wall : gameplay->walls) {
		if (wall.intersects(bbox)) {

			auto intersection = cw::geometry::rectangle::intersection(bbox, wall);
			if (intersection.Height > intersection.Width)
			{
				if (position.x > wall.centre().x)
				{
					set_position(glm::vec2(position.x + intersection.Width, position.y));
				}
				else
				{
					set_position(glm::vec2(position.x - intersection.Width, position.y));
				}

			}
			else
			{
				if (position.y > wall.centre().y)
				{
					set_position(glm::vec2(position.x, position.y + intersection.Height));
				}
				else
				{
					set_position(glm::vec2(position.x, position.y - intersection.Height));
				}

			}

			/*if (intersection.top() - 2 >= wall->bbox.top())
			{
				set_position(glm::vec2(bbox.centre().x, bbox.centre().y - 1));
			}

			if(intersection.bottom() + 2 <= wall->bbox.bottom())
			{
				set_position(glm::vec2(bbox.centre().x, bbox.centre().y + 1));
			}
			
			if (intersection.left() - 2 <= wall->bbox.left())
			{
				set_position(glm::vec2(bbox.centre().x - 1, bbox.centre().y));
			}

			if (intersection.right() + 2 >= wall->bbox.left())
			{
				set_position(glm::vec2(bbox.centre().x + 1, bbox.centre().y));
			}*/
			/*
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
			}*/
			collisions["terra"] = "wall";
		}
	}

	for (auto door : gameplay->doors) {
		if (door.second.intersects(bbox)) {
			if (door.first == "city") {
				if (!battle_trigger) {
					battle_trigger = true;


					core->engine->stage->unload_scene("gameplay");
					this->gameplay = nullptr;
					std::string battle_back_path =
						"resources/assets/ffvi/sprites/Battlebacks/001-Plain01.png";

					std::vector<std::shared_ptr<base> > player_party;
					std::vector<std::shared_ptr<base> > enemy_party;

					player_party.push_back(shared_from_this());
					enemy_party.push_back(shared_from_this());

					auto battle_scene = 
						std::make_shared<game::scenes::battle>(battle_back_path, 
															   player_party,
															   enemy_party);

					auto camera = core->engine->stage->create_camera(glm::i32vec2(640, 480));

					battle_scene->add_camera("main_camera", camera);
					battle_scene->set_camera("main_camera");

					core->engine->stage->add_scene(battle_scene);
					core->engine->stage->load_scene("battle");

				}
				
			}
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

void game::characters::terra::logic(const float& delta) {
	animation_time += delta;

	/*auto character = this->get_rigid_body("terra");
	glm::vec3 b_origin(character->get_origin().x,
					   character->get_origin().y,
					   character->get_origin().z);*/
	
	const float walk_speed = floor(256 * delta);

	if (core->input->is_key_down("Right")) {
		walking_direction_facing = walking_direction::right;

		glm::vec2 origin = get_position();

		auto speed = glm::vec3(origin.x + walk_speed, origin.y, 0);

		set_position(speed);

		idle_right = false;
	}
	else {
		idle_right = true;
	}


	if (core->input->is_key_down("Left")) {
		walking_direction_facing = walking_direction::left;

		glm::vec2 origin = get_position();

		auto speed = glm::vec3(origin.x - walk_speed, origin.y, 0);

		set_position(speed);

		idle_left = false;
	}
	else {
		idle_left = true;
	}

	if (core->input->is_key_down("Up")) {

		walking_direction_facing = walking_direction::up;

		glm::vec2 origin = get_position();

		auto speed = glm::vec3(origin.x, origin.y + walk_speed, 0);

		set_position(speed);

		idle_up = false;
	} else {
		idle_up = true;
	}

	if (core->input->is_key_down("Down")) {
		walking_direction_facing = walking_direction::down;

		glm::vec2 origin = get_position();

		auto speed = glm::vec3(origin.x, origin.y - walk_speed, 0);

		set_position(speed);

		idle_down = false;
	} else {
		idle_down = true;
	}


	find_collisions();

	if (animation_time >= 0.0625f) {
		animation_time = 0.0f;

		sprite_index++;

		if (sprite_index == 3) {
			sprite_index = 0;
		}

	}

	if (walking_direction_facing == walking_direction::up) {
		if (idle_up) {
			current_sprite = animations["up"][1];
		}
		else {
			current_sprite = animations["up"][sprite_index];
		}
	}

	if (walking_direction_facing == walking_direction::down) {
		if (idle_down) {
			current_sprite = animations["down"][1];
		}
		else {
			current_sprite = animations["down"][sprite_index];
		}
	}

	if (walking_direction_facing == walking_direction::left) {
		if (idle_left) {
			current_sprite = animations["left"][1];
		}
		else {
			current_sprite = animations["left"][sprite_index];
		}

		for (auto sprite : sprites) {
			if (sprite->get_h_flip()) {
				sprite->h_flip();
			}
		}

	}

	if (walking_direction_facing == walking_direction::right) {
		if (idle_right) {
			current_sprite = animations["right"][1];
		} else {
			current_sprite = animations["right"][sprite_index];
		}

		for (auto sprite : sprites) {
			if (!sprite->get_h_flip()) {
				sprite->h_flip();
			}
		}

		
	}


}



void game::characters::terra::draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) {

	renderer->upload(current_sprite);
	renderer->debug_renderer->debug_draw(glm::vec4(bbox.X, bbox.Y, bbox.Width, bbox.Height));
}