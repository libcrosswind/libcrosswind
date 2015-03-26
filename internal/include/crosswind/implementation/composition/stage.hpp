#pragma once

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/stage.hpp>
#include <crosswind/interface/composition/scene.hpp>

namespace cw{
namespace implementation{
namespace composition{

	class stage;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::implementation::composition::stage: public cw::interface::composition::stage{
public:
	stage(std::shared_ptr<interface::composition::core> core_ptr){
		core = core_ptr;
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

	virtual void add_scene(std::shared_ptr<interface::composition::scene> scene){

		post_event([this, scene](){
		    scene->core = core;

		    if(scenes.empty()){
			    this->scenes["current"] = scene;
		    }

		    this->scenes[scene->get_name()] = scene;
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

	virtual void update(float dt){
		handle_events();

		for(auto& scene_mapping : scenes){
				scene_mapping.second->update(dt);
		}
	}

	virtual void set_scene_map(const scene_map& new_scene_map){
		scenes = new_scene_map;
	}

	virtual scene_map& get_scene_map(){
		return scenes;
	}

	virtual std::shared_ptr<interface::composition::scene> get_scene(const std::string& scene_name){
		return scenes[scene_name];
	}

private:
	std::shared_ptr<interface::composition::core> core;


};// class scene