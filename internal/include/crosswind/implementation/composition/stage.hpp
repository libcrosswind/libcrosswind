#pragma once

#include <stdexcept>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/stage.hpp>
#include <crosswind/implementation/composition/scene.hpp>

namespace cw{
namespace implementation{
namespace composition{

	class stage;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::implementation::composition::stage: public cw::interface::composition::stage{
public:
	stage(std::shared_ptr<interface::composition::core> c_core): interface::composition::stage(c_core){

	}

	virtual void handle_events(){

		for(auto& event : event_queue){
			event();
		}

		event_queue.clear();
	}

	void post_event(const std::function<void()>& event){
		event_queue.push_back(event);
	}

	virtual scene_ptr create_scene(){

		auto scene = std::make_shared<class scene>();
		scene->core = core;
		return scene;

	}

	std::shared_ptr<actor> create_actor(){
		auto actor = std::make_shared<class actor>();
		actor->core = core;
		return actor;
	}

	virtual void add_scene(const std::string& scene_name, scene_ptr scene){

		post_event([this, scene, scene_name](){
			scene->set_name(scene_name);

			if(scenes.empty()){
				this->scenes["current"] = scene;
			}

			this->scenes[scene_name] = scene;
		});

	}

	virtual scene_ptr get_scene(const std::string& scene_name){
		if(scenes.find(scene_name) != scenes.end()){
			return scenes[scene_name];
		} else {
			throw std::runtime_error("Could not find: " + scene_name);
		}

	}


	virtual void load_scene(const std::string& name){

		post_event([this, name](){
		    this->scenes[name]->init();
		});

	}

	virtual void unload_scene(const std::string& name){

		post_event([this, name](){
		    this->scenes[name]->deinit();
		});

	}


	virtual void swap_scene(const std::string& previous_scene, const std::string& new_scene){

		post_event([this, previous_scene, new_scene](){
		    scenes[previous_scene] = scenes[new_scene];
		});

	}

	virtual void remove_scene(const std::string& scene_name){

		post_event([this, scene_name](){
		    scenes.erase(scene_name);
		});

	}

	virtual void update(const float& dt){
		handle_events();

		scenes["current"]->update(dt);
	}

	virtual void set_scene_map(const scene_map& new_scene_map){
		scenes = new_scene_map;
	}

	virtual scene_map& get_scene_map(){
		return scenes;
	}



};// class scene