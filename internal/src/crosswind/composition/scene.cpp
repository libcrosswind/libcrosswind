#include <stdexcept>

#include "crosswind/composition/scene.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/composition/camera.hpp"
#include "crosswind/simulation/physics.hpp"

cw::composition::scene::scene(const std::string& c_name): named_component(c_name){

}

void cw::composition::scene::add_camera(const std::string& camera_name, std::shared_ptr<camera> camera){

	if(camera_map.empty()){
		camera_map["current"] = camera;
	}
	camera_map[camera_name] = camera;

}

void cw::composition::scene::set_camera(const std::string& camera_name) {
	camera_map["current"] = camera_map[camera_name];
}


std::shared_ptr<cw::composition::camera> cw::composition::scene::get_camera(const std::string& camera_name){

	if(camera_map.find(camera_name) != camera_map.end()){
		return camera_map[camera_name];
	} else {
		throw std::runtime_error("Could not find camera: " + camera_name);
	}
}

auto& cw::composition::scene::get_camera_map(){

	return camera_map;

}

void cw::composition::scene::update(const float& delta){

	for(auto& camera_mapping : camera_map){
		camera_mapping.second->update(delta);
    }

	logic(delta);
}
