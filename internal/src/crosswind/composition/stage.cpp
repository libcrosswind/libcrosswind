#include <stdexcept>

#include "crosswind/composition/stage.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/composition/scene.hpp"
#include "crosswind/composition/camera.hpp"

cw::composition::stage::stage(std::shared_ptr<cw::composition::core> c_core): core(c_core){

}

std::shared_ptr<cw::composition::scene> cw::composition::stage::create_scene(const std::string& f_name){

	auto scene = std::make_shared<class scene>(f_name);
	scene->core = core;
	return scene;

}

std::shared_ptr<cw::composition::camera> cw::composition::stage::create_camera(const glm::i32vec2& f_size){
	return std::make_shared<class camera>(f_size);
}

void cw::composition::stage::add_scene(const std::string& scene_name, std::shared_ptr<scene> scene){
	scene->set_name(scene_name);

	if(scene_map.empty()){
		this->scene_map["current"] = scene;
	}

	this->scene_map[scene_name] = scene;

}

std::shared_ptr<cw::composition::scene> cw::composition::stage::get_scene(const std::string& scene_name){
	if(scene_map.find(scene_name) != scene_map.end()){
		return scene_map[scene_name];
	} else {
		throw std::runtime_error("Could not find scene: " + scene_name);
	}

}

void cw::composition::stage::remove_scene(const std::string& scene_name){

    scene_map.erase(scene_name);

}

void cw::composition::stage::load_scene(const std::string& name){

    this->scene_map[name]->init();
}

void cw::composition::stage::unload_scene(const std::string& name){

    this->scene_map[name]->deinit();

}

void cw::composition::stage::swap_scene(const std::string& previous_scene, const std::string& new_scene){

    scene_map[previous_scene] = scene_map[new_scene];

}

void cw::composition::stage::update(const float& dt){
	scene_map["current"]->update(dt);
}
