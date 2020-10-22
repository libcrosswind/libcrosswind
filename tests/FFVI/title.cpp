#pragma once 

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/composition/core.hpp>
#include <crosswind/composition/scene.hpp>
#include <crosswind/composition/camera.hpp>
#include <crosswind/composition/core.hpp>

#include <title.hpp>
#include <sega_logo.hpp>
/*#include <characters/title/team_logo.hpp>

#include <characters/title/title_background.hpp>*/

#include <crosswind/sound/mixer.hpp>

#include <crosswind/graphical/opengl/renderer.hpp>

#include <crosswind/composition/core.hpp>
#include <crosswind/graphical/video.hpp>

#include <crosswind/composition/tilemap.hpp>

#include <crosswind/engine.hpp>

#include <crosswind/composition/stage.hpp>

#include <crosswind/composition/camera.hpp>

#include <crosswind/composition/sprite_set.hpp>
#include <crosswind/composition/physical.hpp>

#include <crosswind/simulation/detail/body.hpp>

#include <terra.hpp>

game::scenes::title::title() : scene("title") {
}
game::scenes::title::~title() {
	core->video->unload_model("resources/assets/ffvi/sprites/square_logo.json");
	core->mixer->unload_music("battle_bgm");
}

void game::scenes::title::init() {

	/*auto main_camera = std::make_shared<cw::composition::camera>(core->video->get_window_size());
	add_camera("main_camera", main_camera);
	set_camera("main_camera");*/
	tilemap = 
		std::make_shared<cw::composition::tilemap>(core, 
												   "resources/assets/ffvi/tilemaps/Library.json");
	terra = std::make_shared<game::characters::title::terra>(core,
		"resources/assets/sonic_the_hedgehog/graphics/characters/jeshejojo/jeshejojo.json");

	for (auto& tile_object : tilemap->objects) {
		if (tile_object.getName() == "wall") {
			auto physical = std::make_shared<cw::composition::physical>(core, "wall");
			auto pos = tile_object.getPosition();
			auto size = tile_object.getSize();

			auto map_size = tilemap->map->getSize();
			auto tile_size = tilemap->map->getTilesets().front().getTileSize();
			auto pos_x = pos.x + size.x / 2.0f - tile_size.x / 2.0f;
			auto pos_y = pos.y + size.y / 2.0f - tile_size.y / 2.0f;
			physical->add_rigid_body("wall",
				glm::vec3(pos_x, 
						  -pos_y, 0.0f),
				glm::vec3(size.x, size.y, 10.0f),
				0.0f);

			auto body = physical->get_rigid_body("wall");
			//body->set_origin(glm::vec3(0.5f, 0.5f, 0));
			walls.push_back(physical);
		}
		
	}

	title_model = core->video->load_model(glm::vec3(0.0f, 0.0f, 0.0f),
										  glm::vec3(225.0f, 225.0f, 0.0f),
										  "resources/assets/ffvi/sprites/square_logo.json");
	 
	core->mixer->load_music("battle_bgm", "resources/assets/ffvi/audio/bgm/battle_theme.ogg");



	//core->mixer->load_music("title_bgm", "assets/sonic_the_hedgehog/audio/bgm/sonic/title_bgm.ogg");

	//auto sega_logo = std::make_shared<characters::title::sega_logo>();
	//auto team_logo = this->create_actor<characters::title::team_logo>();
	//auto title_background = this->create_actor<game::characters::title::title_background>();

	//	    add_actor("sega_logo", sega_logo);
	//	    add_actor("team_logo", team_logo);
	//add_actor("title_background", title_background);

	/*
	for (auto& actor : actors) {
		actor.second->init();
	}*/

	reset();
}

void game::scenes::title::deinit() {

}

void game::scenes::title::reset() {
	get_camera("main_camera")->set_position(glm::vec3(0.0f, 0.0f, 0.0f));

	sega_sound_ongoing = false;
	title_sound_ongoing = false;
	sega_logo_duration = 8.0f;
	team_logo_duration = 8.0f;
	time_count = 0.0f;

	//core->video->window->set_clear_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//		get_actor("sega_logo")->set_alpha(0.0f);
	//		get_actor("team_logo")->set_alpha(0.0f);
	//get_actor("title_background")->set_alpha(0.0f);
	phase = scene_phase::title_logo;

}

/*void draw_sega_logo() {

	if (time_count <= sega_logo_duration) {

		if (time_count <= 2.0f) {
			float alpha_blending = glm::sin(glm::radians(time_count / 2.0f * 90.0f));
			get_actor("sega_logo")->set_alpha(alpha_blending);
		}
		else if (!sega_sound_ongoing) {
			sega_sound_ongoing = true;
			core->mixer->play_music("logo_bgm", 0);
		}
		else if (time_count >= 6.0f && time_count <= 8.0f) {

			const float time_range = 2.0f - (8.0f - time_count);

			float alpha_blending = glm::sin(glm::radians((time_range / 2.0f * 90.0f) + 90.0f));
			get_actor("sega_logo")->set_alpha(alpha_blending);
			core->video->window->set_clear_color(glm::vec4(alpha_blending, alpha_blending, alpha_blending, 1.0f));
		}

	}
	else {
		time_count = 0.0f;
		phase = scene_phase::team_logo;
	}

}

void draw_team_logo() {

	if (time_count <= sega_logo_duration) {

		float alpha_blending = glm::sin(glm::radians(time_count / sega_logo_duration * 180.0f));
		get_actor("team_logo")->set_alpha(alpha_blending);

	}
	else {
		time_count = 0.0f;
		phase = scene_phase::title_logo;
	}

}*/

void game::scenes::title::draw_title() {

	if (time_count <= 1.0f) {
		/*this->get_actor("title_background")->get_model("title_sonic")->change_animation("title_sonic_a");

		this->get_actor("title_background")->get_model("title_logo_a")->set_origin(glm::vec3(0.0f, 0.0f, 0.0f));
		this->get_actor("title_background")->get_model("title_sonic")->set_origin(glm::vec3(-2000.0f, -41.0f, 0.0f));
		this->get_actor("title_background")->get_model("title_logo_b")->set_origin(glm::vec3(0.0f, 0.0f, 0.0f));

		float alpha_blending = glm::sin(glm::radians(time_count / 1.0f * 90.0f));
		this->get_actor("title_background")->set_alpha(alpha_blending);*/

	}
	else if (time_count >= 1.0f && time_count <= 2.0f) {

	}
	else if (time_count >= 2.0f && time_count <= 2.5f) {

		/*
		const float sonic_y = this->get_actor("title_background")->get_model("title_sonic")->get_origin().y;
		const float movement_time = 4.05f; //3.0f - (4.0f - time_count);

		const float movement = glm::clamp(sonic_y + movement_time, -41.0f, 82.0f);
		this->get_actor("title_background")->get_model("title_sonic")->set_origin(glm::vec3(0.0f, movement, 0.0f));

		*/

	}
	else if (time_count >= 2.5f && time_count <= 9.0f) {

		/*if (time_count - 3.0f < 0.9f) {
			this->get_actor("title_background")->get_model("title_sonic")->change_animation("title_sonic_b");
		}
		else {
			this->get_actor("title_background")->get_model("title_sonic")->change_animation("title_sonic_c");
		}

		const float sonic_x = this->get_actor("title_background")->get_model("title_sonic")->get_origin().x +
			2.2;

		this->get_actor("title_background")->get_model("title_logo_a")->set_origin(glm::vec3(sonic_x, 0.0f, 0.0f));
		this->get_actor("title_background")->get_model("title_sonic")->set_origin(glm::vec3(sonic_x, 82.0f, 0.0f));
		this->get_actor("title_background")->get_model("title_logo_b")->set_origin(glm::vec3(sonic_x, 0.0f, 0.0f));
		*/
	}
	else if (time_count >= 9.0f && time_count <= 10.0f) {

		/*this->get_actor("title_background")->get_model("title_sonic")->change_animation("title_sonic_d");

		const float time_range = 2.0f - (10.0f - time_count);

		float alpha_blending = glm::sin(glm::radians((time_range / 2 * 90.0f) + 90.0f));
		get_actor("title_background")->set_alpha(alpha_blending);
		core->video->window->set_clear_color(glm::vec4(alpha_blending, alpha_blending, alpha_blending, 1.0f));
		*/
	}
	else if (time_count >= 10.0f && time_count <= 12.0f) {

	}
	else {
		time_count = 0.0f;
		//reset();
	}

	if (!title_sound_ongoing && time_count >= 1.0f) {
		title_sound_ongoing = true;
		core->mixer->play_music("battle_bgm", -1);
	}

	if (time_count >= 3.0f) {
		/*const float sonic_x = this->get_actor("title_background")->get_model("title_sonic")->get_origin().x;
		get_camera("main_camera")->set_position(glm::vec3(sonic_x, 0.0f, 0.0f));

		*/
	}
}

void game::scenes::title::logic(const float& delta) {

	terra->logic(delta);

	time_count += delta;

	switch (phase) {
	case scene_phase::sega_logo:
		//draw_sega_logo();
//				break;

	case scene_phase::team_logo:
		//draw_team_logo();
//				break;

	case scene_phase::title_logo:
		draw_title();
		break;
	}
}

void game::scenes::title::draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) {
	core->engine->stage->get_scene("current")->get_camera("current")->set_position(glm::vec3(312, -224, 0));

	//renderer->upload(title_model->get_sprite());

	tilemap->draw(renderer);

	terra->draw(renderer);
}
