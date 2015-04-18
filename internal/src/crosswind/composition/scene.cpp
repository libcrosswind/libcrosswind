#include <stdexcept>

#include "crosswind/composition/scene.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/composition/camera.hpp"
#include "crosswind/composition/group.hpp"
#include "crosswind/composition/actor.hpp"
#include "crosswind/simulation/physics.hpp"

cw::composition::scene::scene(){

	collision_map["undefined"] = actor_collision_map();

}

void cw::composition::scene::add_camera(const std::string& camera_name, std::shared_ptr<camera> camera){

	if(camera_map.empty()){
		camera_map["current"] = camera;
	}
	camera_map[camera_name] = camera;

}

std::shared_ptr<cw::composition::camera> cw::composition::scene::get_camera(const std::string& camera_name){

	if(camera_map.find(camera_name) != camera_map.end()){
		return camera_map[camera_name];
	} else {
		throw std::runtime_error("Could not find: " + camera_name);
	}

}

void cw::composition::scene::add_group(const std::string& group_name, std::shared_ptr<group> group){

	group->set_name(group_name);
	group_map[group_name] = group;

}

auto cw::composition::scene::get_group(const std::string& group_name){

	if(group_map.find(group_name) != group_map.end()){
		return group_map[group_name];
	} else {
		throw std::runtime_error("Could not find: " + group_name);
	}

}

void cw::composition::scene::remove_group(const std::string& group_name){

	if(group_map.find(group_name) != group_map.end()){
		group_map.erase(group_name);
	} else {
		throw std::runtime_error(group_name + " does not exist or was already removed");
	}

}

void cw::composition::scene::load_group(const std::string& group_name){

	get_group(group_name)->init();

}

void cw::composition::scene::unload_group(const std::string& group_name){

	get_group(group_name)->deinit();

}

void cw::composition::scene::add_actor(const std::string& actor_name, std::shared_ptr<actor> actor){

	actor->set_name(actor_name);
	actor_map[actor_name] = actor;

}

auto cw::composition::scene::get_actor(const std::string& actor_name){

	if(actor_map.find(actor_name) != actor_map.end()){
		return actor_map[actor_name];
	} else {
		throw std::runtime_error("Could not find: " + actor_name);
	}

}

void cw::composition::scene::remove_actor(const std::string& actor_name){

	if(actor_map.find(actor_name) != actor_map.end()){
		actor_map.erase(actor_name);
	} else {
		throw std::runtime_error(actor_name + " does not exist or was already removed");
	}

}

void cw::composition::scene::load_actor(const std::string& actor_name){

	get_actor(actor_name)->init();

}

void cw::composition::scene::unload_actor(const std::string& actor_name){

	get_actor(actor_name)->deinit();

}

auto& cw::composition::scene::get_camera_map(){

	return camera_map;

}

std::map<std::string, std::shared_ptr<cw::composition::group> >& cw::composition::scene::get_group_map(){

	return group_map;

}

std::map<std::string, std::shared_ptr<cw::composition::actor> >& cw::composition::scene::get_actor_map(){

	return actor_map;

}

void cw::composition::scene::check_collisions(){

	int numManifolds = core->physics->get_collision_manifolds_number();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold = core->physics->get_manifold_by_index(i);

		int num_contacts = contactManifold->getNumContacts();
		if (num_contacts){

			const btCollisionObject* obA = contactManifold->getBody0();
			const btCollisionObject* obB = contactManifold->getBody1();


			auto& a_name = static_cast<actor*>(obA->getUserPointer())->get_name();
			auto& b_name = static_cast<actor*>(obB->getUserPointer())->get_name();

			for(int j = 0; j<num_contacts; j++){
				btManifoldPoint& contact = contactManifold->getContactPoint(j);

				glm::vec3 a(contact.m_localPointA.x(), contact.m_localPointA.y(), contact.m_localPointA.z());
				glm::vec3 b(contact.m_localPointB.x(), contact.m_localPointB.y(), contact.m_localPointB.z());

				collision_map[a_name][b_name].push_back(std::make_pair(a,b));

			}
		}
	}

}

auto& cw::composition::scene::get_collision_map(const std::string& actor_a){

	if(collision_map.find(actor_a) != collision_map.end()){
		return collision_map[actor_a];
	} else {
		return collision_map["undefined"];
	}

}

void cw::composition::scene::handle_events(){

	std::vector<std::pair<bool, std::function<void()> > > continuous_events;

	for(auto& event_mapping : event_queue){

		if(event_mapping.first == true){
			continuous_events.push_back(event_mapping);
		}

		event_mapping.second();
	}

	event_queue.clear();
	event_queue.insert(event_queue.end(), continuous_events.begin(), continuous_events.end());

}

void cw::composition::scene::post_event(const std::function<void()>& event, const bool& continuous){

	event_queue.push_back(std::make_pair(continuous, event));

}

void cw::composition::scene::update(const float& delta){

	handle_events();
	check_collisions();

	for(auto& camera_mapping : camera_map){
		camera_mapping.second->update(delta);
    }

	for(auto& group_mapping : group_map){
		group_mapping.second->update(delta);
	}

	for(auto& actor_mapping : actor_map){
		actor_mapping.second->update(delta);
    }

	logic(delta);

	collision_map.clear();

}

void cw::composition::scene::set_bool(const std::string item_name, const bool& value){

	conditions[item_name] = value;

}

bool& cw::composition::scene::get_bool(const std::string item_name){

	return conditions[item_name];

}

void cw::composition::scene::set_float(const std::string item_name, const float& value){

	float_values[item_name] = value;

}

float& cw::composition::scene::get_float(const std::string item_name){

	return float_values[item_name];

}

void cw::composition::scene::set_int(const std::string item_name, const int& value){

	int_values[item_name] = value;

}

int& cw::composition::scene::get_int(const std::string item_name){

	return int_values[item_name];

}
