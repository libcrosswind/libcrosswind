#include "crosswind/composition/group.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/composition/actor.hpp"

cw::composition::group::group(){
	
}

void cw::composition::group::set_origin(const glm::vec3& f_origin){
	for (auto &actor : actor_map) {
		auto translated_origin = actor.second->get_origin() + f_origin - origin;
		actor.second->set_origin(translated_origin);
	}

	origin = f_origin;
}

void cw::composition::group::set_size(const glm::vec3& f_size){
	for (auto &actor : actor_map) {
		auto percented_size = actor.second->get_size() * f_size / size;
		actor.second->set_size(percented_size);
	}

	size = f_size;
}

void cw::composition::group::set_alpha(const float& f_alpha){
	alpha = f_alpha;
	for (auto &actor : actor_map) {
		actor.second->set_alpha(alpha);
	}
}

void cw::composition::group::add_group(const std::string& group_name, std::shared_ptr<group> new_group){
	group_map[group_name] = new_group;
}

std::shared_ptr<cw::composition::group> cw::composition::group::get_group(const std::string& group_name){
	return group_map[group_name];
}

void cw::composition::group::remove_group(const std::string& group_name){
	group_map.erase(group_name);
}


void cw::composition::group::add_actor(const std::string& actor_name, std::shared_ptr<actor> new_actor){
	actor_map[actor_name] = new_actor;
}

std::shared_ptr<cw::composition::actor> cw::composition::group::get_actor(const std::string& actor_name){
	return actor_map[actor_name];
}

void cw::composition::group::remove_actor(const std::string& actor_name){
	actor_map.erase(actor_name);
}

std::map<std::string, std::shared_ptr<cw::composition::group> >& cw::composition::group::get_group_map(){
	return group_map;
}

std::map<std::string, std::shared_ptr<cw::composition::actor> >& cw::composition::group::get_actor_map(){
	return actor_map;
}

void cw::composition::group::update(const float& delta){
	for(auto& actor_mapping : actor_map){
		actor_mapping.second->update(delta);
	}

	logic(delta);
}
