#include "crosswind/graphical/object/model.hpp"

cw::graphical::object::model::model() {

}

void cw::graphical::object::model::change_animation(const std::string& new_animation, const bool& x_orientation) {

	if (animations["current"] != animations[new_animation]) {
		animations["current"] = animations[new_animation];
		animations["current"]->flip(x_orientation);
	}
}

void cw::graphical::object::model::update(const float& delta) {

	delta_count += delta;

	if (delta_count >= animations["current"]->duration / (float)animations["current"]->frames.size()) {

		delta_count = 0;

		animations["current"]->current_frame++;

		if (animations["current"]->current_frame >= animations["current"]->frames.size()) {
			animations["current"]->current_frame = 0;
		}
	}

	render_sprite_list["current"] = animations["current"]->frames[animations["current"]->current_frame];

}

std::shared_ptr<cw::graphical::object::sprite> cw::graphical::object::model::get_sprite() {
	return render_sprite_list["current"];
}

std::map<std::string, std::shared_ptr<cw::graphical::object::sprite> >& cw::graphical::object::model::get_render_sprite_list() {
	return render_sprite_list;
}

void cw::graphical::object::model::set_animations(std::map<std::string, std::shared_ptr<cw::graphical::object::sprite_animation> >& new_animations) {

	animations.clear();

	for (auto mapping : new_animations) {
		animations[mapping.first] = mapping.second;
	}
}

std::map<std::string, std::shared_ptr<cw::graphical::object::sprite_animation> >& cw::graphical::object::model::get_animations() {
	return animations;
}

void cw::graphical::object::model::set_origin(const glm::vec3& new_origin) {
	origin = new_origin;
	for (auto& animation : animations) {
		for (auto& frame : animation.second->frames) {
			frame->set_origin(origin);
		}
	}
}

glm::vec3 cw::graphical::object::model::get_origin() {
	return origin;
}

void cw::graphical::object::model::set_size(const glm::vec3& new_size) {
	size = new_size;
}

glm::vec3 cw::graphical::object::model::get_size() {
	return size;
}