#pragma once 

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/composition/core.hpp>
#include <crosswind/composition/scene.hpp>
#include <crosswind/composition/camera.hpp>
#include <crosswind/composition/core.hpp>

#include <gameplay.hpp>
#include <sega_logo.hpp>
/*#include <characters/title/team_logo.hpp>

#include <characters/title/title_background.hpp>*/

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

#include <terra.hpp>

game::scenes::gameplay::gameplay() : scene("gameplay") {
}
game::scenes::gameplay::~gameplay() {
	core->mixer->unload_music("coin_song");
}

void game::scenes::gameplay::init() {

	tilemap = 
		std::make_shared<cw::composition::tilemap>(core, 
												   "resources/assets/ffvi/tilemaps/Library.json");

	terra = std::make_shared<game::characters::terra>(core, shared_from_this(),
		"resources/assets/ffvi/sprites/terra.json");

	for (auto& tile_object : tilemap->objects) {
		if (tile_object.getType() == "wall") {
			auto pos = tile_object.getPosition();
			auto size = tile_object.getSize();

			auto map_size = tilemap->map->getSize();
			auto tile_size = tilemap->map->getTilesets().front().getTileSize();
			auto pos_x = pos.x - tile_size.x / 2.0f;
			auto pos_y = -pos.y + map_size.y * tile_size.y - size.y + tile_size.y / 2.0f;

			cw::geometry::rectangle bbox = cw::geometry::rectangle({ pos_x,
											 pos_y },
											{ size.x, size.y });

			walls.push_back(bbox);
		}
		else if (tile_object.getType() == "door") {
			auto pos = tile_object.getPosition();
			auto size = tile_object.getSize();

			auto map_size = tilemap->map->getSize();
			auto tile_size = tilemap->map->getTilesets().front().getTileSize();
			auto pos_x = pos.x - tile_size.x / 2.0f;
			auto pos_y = -pos.y + map_size.y * tile_size.y - size.y + tile_size.y / 2.0f;

			cw::geometry::rectangle bbox = cw::geometry::rectangle({ pos_x,
											 pos_y },
				{ size.x, size.y });

			doors[tile_object.getName()] = bbox;
		}
		
	}
	 
	core->mixer->load_music("coin_song", "resources/assets/ffvi/audio/bgm/coin_song.ogg");

	core->mixer->play_music("coin_song", -1);

 }

void game::scenes::gameplay::deinit() {

}
 

void game::scenes::gameplay::logic(const float& delta) {

	terra->logic(delta);
}

void game::scenes::gameplay::draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) {
	
	core->
		engine->
		stage->
		get_scene("current")->
		get_camera("current")->set_position(glm::vec3(312, 224, 0));

	tilemap->draw(renderer);

	for (auto& wall : walls) {
		auto bbox = wall;
		renderer->debug_renderer->debug_draw(glm::vec4(bbox.X, bbox.Y, bbox.Width, bbox.Height));
	}

	terra->draw(renderer);
}
