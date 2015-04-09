#pragma once

#include <stdexcept>
#include <memory>
#include <functional>
#include <string>

#include <crosswind/implementation/composition/core.hpp>
#include <crosswind/implementation/composition/scene.hpp>
#include <crosswind/implementation/composition/camera.hpp>
#include <crosswind/implementation/composition/actor.hpp>
#include <crosswind/implementation/composition/group.hpp>

namespace cw{
namespace implementation{
namespace composition{

	class stage;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::implementation::composition::stage{
public:
	stage(std::shared_ptr<core> c_core): core(c_core){
	}

	void handle_events(){

		for(auto& event : event_queue){
			event();
		}

		event_queue.clear();
	}

	void post_event(const std::function<void()>& event){
		event_queue.push_back(event);
	}

	auto create_scene(){

		auto scene = std::make_shared<class scene>();
		scene->core = core;
		return scene;

	}

	auto create_camera(const glm::i32vec2& f_size){
		return std::make_shared<class camera>(f_size);
	}

	auto create_actor(){
		auto actor = std::make_shared<class actor>();
		actor->core = core;
		return actor;
	}

	auto create_group(){
		auto group = std::make_shared<class group>();
		group->core = core;
		return group;
	}

	void add_scene(const std::string& scene_name, std::shared_ptr<scene> scene){

		post_event([this, scene, scene_name](){
			scene->set_name(scene_name);

			if(scene_map.empty()){
				this->scene_map["current"] = scene;
			}

			this->scene_map[scene_name] = scene;
		});

	}	

	auto get_scene(const std::string& scene_name){
		if(scene_map.find(scene_name) != scene_map.end()){
			return scene_map[scene_name];
		} else {
			throw std::runtime_error("Could not find: " + scene_name);
		}

	}

	void remove_scene(const std::string& scene_name){

		post_event([this, scene_name](){
			scene_map.erase(scene_name);
		});

	}

	void load_scene(const std::string& name){

		post_event([this, name](){
		    this->scene_map[name]->init();
		});

	}

	void unload_scene(const std::string& name){

		post_event([this, name](){
		    this->scene_map[name]->deinit();
		});

	}

	void swap_scene(const std::string& previous_scene, const std::string& new_scene){

		post_event([this, previous_scene, new_scene](){
			scene_map[previous_scene] = scene_map[new_scene];
		});

	}

	void update(const float& dt){
		handle_events();

		scene_map["current"]->update(dt);
	}

private:
	std::shared_ptr<core> core;
	std::map<std::string, std::shared_ptr<scene> > scene_map;
	std::vector<std::function<void()> > event_queue;

};// class stage