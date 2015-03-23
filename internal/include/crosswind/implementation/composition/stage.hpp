#pragma once

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
	stage(){
		
	}

	virtual void add_scene(std::shared_ptr<interface::composition::scene> scene){

	}

	virtual void swap_scene(const std::string& previous_scene, const std::string& new_scene){

	}

	virtual void remove_scene(const std::string& scene_name){

	}

	virtual void update(float dt){

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

};// class scene