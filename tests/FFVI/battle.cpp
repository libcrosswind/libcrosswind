#pragma once 

#include <iostream>
#include <memory>

#include <glm/glm.hpp>

#include <crosswind/composition/core.hpp>
#include <crosswind/composition/scene.hpp>
#include <crosswind/composition/camera.hpp>
#include <crosswind/composition/core.hpp>

#include <battle.hpp>

#include <crosswind/sound/mixer.hpp>

#include <crosswind/graphical/opengl/renderer.hpp>
#include <crosswind/graphical/opengl/debug_renderer.hpp>

#include <crosswind/composition/core.hpp>
#include <crosswind/graphical/video.hpp>

#include <crosswind/composition/tilemap.hpp>

#include <crosswind/engine.hpp>

#include <crosswind/composition/stage.hpp>

#include <crosswind/composition/camera.hpp>

#include <crosswind/composition/sprite_set.hpp>
#include <crosswind/composition/physical.hpp>

#include <crosswind/simulation/detail/body.hpp>

#include <crosswind/graphical/opengl/texture.hpp>

#include "base.hpp"

game::scenes::battle::battle(const std::string& battle_back_path,
							 std::vector<std::shared_ptr<game::characters::base> > player_party,
							 std::vector<std::shared_ptr<game::characters::base> > enemy_party)
: scene("battle"), player_party(player_party), enemy_party(enemy_party) {
	this->battle_back_path = battle_back_path;
	this->ui_path = "resources/assets/ffvi/sprites/Windowskins/Window01.png";

}
game::scenes::battle::~battle() {
	core->mixer->unload_music("battle_bgm");
	core->video->remove_texture(battle_back_path);
	core->video->remove_texture(ui_path);
}

void game::scenes::battle::init() {
	auto bback_texture = core->video->load_texture(battle_back_path, battle_back_path);
	battle_back = core->video->load_sprite(battle_back_path, 
										   glm::vec3(bback_texture->size.x, bback_texture->size.y, 0));


	auto ui_texture = core->video->load_texture(ui_path, ui_path);

	e_window_background = core->video->load_sprite(ui_path, 
											     glm::vec3(640 / 3 - 6 * 3, 480 / 4 - 5 * 4, 0),
												 glm::vec4(0.0f, 0.5f, 0.5f, 1.0f));

	e_window_foreground = core->video->load_sprite(ui_path, 
											     glm::vec3(640 / 3, 480 / 4, 0),
												 glm::vec4(0.5f, 0.5f, 1.0f, 1.0f));

	e_window_background->set_origin(glm::vec3(-320 + window_background->get_size().x * 0.5f,
											-240 + window_background->get_size().y * 0.5f + 5 * 2,
										    0));

	e_window_foreground->set_origin(glm::vec3(-320 + window_foreground->get_size().x * 0.5f,
											-240 + window_foreground->get_size().y * 0.5f,
										    0));

	core->mixer->load_music("battle_bgm", "resources/assets/ffvi/audio/bgm/battle_theme.ogg");
	core->mixer->play_music("battle_bgm", -1);
}

void game::scenes::battle::deinit() {

}


void game::scenes::battle::logic(const float& delta) {


	for (auto player : player_party) {
		player->logic(delta);
		player->set_position(glm::vec2(0, 0));
	}
}

void game::scenes::battle::draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) {
	core->
		engine->
		stage->
		get_scene("current")->
		get_camera("current")->set_position(glm::vec3(0, 0, 0));

	renderer->upload(battle_back);

	for (auto player : player_party) {
		renderer->upload(player->current_sprite);
	}

	renderer->upload(e_window_background);
	renderer->upload(e_window_foreground);

}
