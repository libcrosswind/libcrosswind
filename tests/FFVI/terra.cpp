#include <terra.hpp>

#include <filesystem>

#include "crosswind/composition/tilemap.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/graphical/video.hpp"

#include "crosswind/graphical/opengl/texture.hpp"
#include "crosswind/graphical/opengl/renderer.hpp"

#include "crosswind/graphical/object/sprite.hpp"

game::characters::title::terra::terra(std::shared_ptr<cw::composition::core> core, const std::string& path) :
	sprite_set(core, path) {
	current_sprite = sprites.at(0);
	animation_time = 0.0f;

	for (auto sprite : sprites) {
		sprite->set_origin(glm::vec3(1024 / 2.0f, -768 / 2.0f, 0));
	}

}

void game::characters::title::terra::logic(const float& delta) {
	animation_time += delta;

	if (animation_time >= 0.0625f) {
		animation_time = 0.0f;

		sprite_index++;

		if (sprite_index == 6 || sprite_index == 6) {
			sprite_index = 0;
		}

		if (sprite_index >= sprites.size()) {
			sprite_index = 0;
		}

		current_sprite = sprites.at(sprite_index);
	}
}



void game::characters::title::terra::draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) {

	renderer->upload(current_sprite);
}