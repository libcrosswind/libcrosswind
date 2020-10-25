#include "crosswind/graphical/object/sprite.hpp"

#include "base.hpp"

game::characters::base::base(std::shared_ptr<cw::composition::core> core, const std::string& path) :
	sprite_set(core, path) {

}

void game::characters::base::set_position(const glm::vec2& new_position) {

	for (auto sprite : sprites) {
		sprite->set_origin(glm::vec3(new_position.x, new_position.y, -1));
	}

	int bbox_new_x = new_position.x - bbox.Width / 2;
	int bbox_new_y = new_position.y - bbox.Height / 2;

	bbox.X = bbox_new_x;
	bbox.Y = bbox_new_y;

	position = new_position;
}

glm::vec2 game::characters::base::get_position() {
	return position;
}
