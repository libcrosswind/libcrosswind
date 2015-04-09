#pragma once 

#include <memory>
#include <stdexcept>
#include <functional>

#include <crosswind/interface/composition/named_component.hpp>
#include <crosswind/interface/composition/logic_component.hpp>

#include <crosswind/implementation/composition/core.hpp>
#include <crosswind/implementation/composition/actor.hpp>
#include <crosswind/implementation/composition/group.hpp>
#include <crosswind/implementation/composition/camera.hpp>

namespace cw{
namespace implementation{
namespace composition{

	class scene;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::implementation::composition::scene: public cw::interface::composition::named_component,
											  public cw::interface::composition::logic_component{
	typedef std::map<std::string, std::vector<std::pair<glm::vec3, glm::vec3> > > actor_collision_map;
	typedef std::map<std::string, actor_collision_map> scene_collision_map;
	friend class stage;

public:
	scene(){
		collisions["undefined"] = actor_collision_map();
	}

	void add_camera(const std::string& camera_name, std::shared_ptr<camera> camera){
		if(camera_map.empty()){
			camera_map["current"] = camera;
		}
		camera_map[camera_name] = camera;
	}

	auto get_camera(const std::string& camera_name){

		if(camera_map.find(camera_name) != camera_map.end()){
			return camera_map[camera_name];
		} else {
			throw std::runtime_error("Could not find: " + camera_name);
		}
	}

	void add_actor(const std::string& actor_name, std::shared_ptr<actor> actor){
		actor->set_name(actor_name);
		actor_map[actor_name] = actor;
	}

	auto get_actor(const std::string& actor_name){
		if(actor_map.find(actor_name) != actor_map.end()){
			return actor_map[actor_name];
		} else {
			throw std::runtime_error("Could not find: " + actor_name);
		}
	}

	void remove_actor(const std::string& actor_name){
		if(actor_map.find(actor_name) != actor_map.end()){
			actor_map.erase(actor_name);
		} else {
			throw std::runtime_error(actor_name + " does not exist or was already removed");
		}
	}

	void load_actor(const std::string& actor_name){
		get_actor(actor_name)->init();
	}

	void unload_actor(const std::string& actor_name){
		get_actor(actor_name)->deinit();
	}

	void add_group(const std::string& group_name, std::shared_ptr<group> group){
		group->set_name(group_name);
		group_map[group_name] = group;
	}

	auto get_group(const std::string& group_name){
		if(group_map.find(group_name) != group_map.end()){
			return group_map[group_name];
		} else {
			throw std::runtime_error("Could not find: " + group_name);
		}
	}

	void remove_group(const std::string& group_name){
		if(group_map.find(group_name) != group_map.end()){
			group_map.erase(group_name);
		} else {
			throw std::runtime_error(group_name + " does not exist or was already removed");
		}
	}

	void load_group(const std::string& group_name){
		get_group(group_name)->init();
	}

	void unload_group(const std::string& group_name){
		get_group(group_name)->deinit();
	}

	auto& get_camera_map(){
		return camera_map;
	}

	auto& get_group_map(){
		return group_map;
	}

	auto& get_actor_map(){
		return actor_map;
	}

public:
	virtual void check_collisions(){

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

					collisions[a_name][b_name].push_back(std::make_pair(a,b));

				}
			}
		}
	}

	auto& get_collision_map(const std::string& actor_a){

		if(collisions.find(actor_a) != collisions.end()){
			return collisions[actor_a];
		} else {
			return collisions["undefined"];
		}

	}

private:
	virtual void handle_events(){
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

public:
	void post_event(const std::function<void()>& event, const bool& continuous = false){
		event_queue.push_back(std::make_pair(continuous, event));
	}

	virtual void update(const float& delta){
		handle_events();
		check_collisions();

		for(auto& camera : camera_map){
           camera.second->update(delta);
        }

		for(auto& group : group_map){
			for(auto& actor : group.second->get_actor_map()){
				actor.second->update(delta);
			}
		}

		for(auto& actor : actor_map){
           actor.second->update(delta);
        }

		logic(delta);

		collisions.clear();
	}

public:
	std::shared_ptr<core> core;

public:
	void set_bool(const std::string item_name, const bool& value){
		conditions[item_name] = value;
	}

	bool& get_bool(const std::string item_name){
		return conditions[item_name];
	}

	void set_float(const std::string item_name, const float& value){
		float_values[item_name] = value;
	}

	float& get_float(const std::string item_name){
		return float_values[item_name];
	}

	void set_int(const std::string item_name, const int& value){
		int_values[item_name] = value;
	}

	int& get_int(const std::string item_name){
		return int_values[item_name];
	}


private:
	std::map<std::string, bool> conditions;
	std::map<std::string, float> float_values;
	std::map<std::string, int> int_values;

	std::map<std::string, std::shared_ptr<actor> > actor_map;
	std::map<std::string, std::shared_ptr<group> > group_map;
	std::map<std::string, std::shared_ptr<camera> > camera_map;
	std::vector<std::pair<bool, std::function<void()> > > event_queue;
	scene_collision_map collisions;


};// class stage