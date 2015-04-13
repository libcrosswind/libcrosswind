#include "crosswind/composition/group.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/composition/actor.hpp"

cw::composition::group::group(){
	
}

virtual void cw::composition::group::set_origin(const glm::vec3& f_origin) override {
	for (auto &actor : actor_map) {
		auto translated_origin = actor.second->get_origin() + f_origin - origin;
		actor.second->set_origin(translated_origin);
	}

	origin = f_origin;
}

virtual void cw::composition::group::set_size(const glm::vec3& f_size) override {
	for (auto &actor : actor_map) {
		auto percented_size = actor.second->get_size() * f_size / size;
		actor.second->set_size(percented_size);
	}

	size = f_size;
}

virtual void cw::composition::group::set_alpha(const float& f_alpha) override {
	alpha = f_alpha;
	for (auto &actor : actor_map) {
		actor.second->set_alpha(alpha);
	}
}

void cw::composition::group::add_actor(const std::string& actor_name, std::shared_ptr<actor> new_actor){
	actor_map[actor_name] = new_actor;
}

auto cw::composition::group::get_actor(const std::string& actor_name){
	return actor_map[actor_name];
}

void cw::composition::group::remove_actor(const std::string& actor_name){
	actor_map.erase(actor_name);
}

auto& cw::composition::group::get_actor_map(){
	return actor_map;
}

void cw::composition::group::update(const float& delta){
	for(auto& actor_mapping : actor_map){
		actor_mapping.second->update(delta);
	}

	logic(delta);
}
