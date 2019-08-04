#include <memory>
#include <string>
#include <stdexcept>

#include "glm/glm.hpp"

#include "crosswind/composition/actor/animated_actor.hpp"
#include "crosswind/composition/core.hpp"
#include "crosswind/platform/filesystem.hpp"
#include "crosswind/graphical/video.hpp"
#include "crosswind/graphical/object/model.hpp"
#include "crosswind/graphical/object/text.hpp"
#include "crosswind/graphical/object/sprite.hpp"
#include "crosswind/graphical/object/sprite_animation.hpp"
#include "crosswind/simulation/physics.hpp"
#include "crosswind/simulation/detail/character.hpp"
#include "crosswind/simulation/detail/body.hpp"

cw::composition::animated_actor::animated_actor(const std::string& c_name): actor(c_name){

}

cw::composition::animated_actor::~animated_actor(){

	for(auto& body_mapping: body_map){
		core->physics->remove_rigid_body(body_mapping.second);
	}

	for(auto& character_mapping: character_map){
		core->physics->remove_character(character_mapping.second);
	}
}

void cw::composition::animated_actor::set_origin(const glm::vec3& f_origin){
	for (auto &model : model_map) {
		auto translated_origin = model.second->get_origin() + f_origin - origin;
		model.second->set_origin(translated_origin);
	}

	origin = f_origin;
}

void cw::composition::animated_actor::set_size(const glm::vec3& f_size){
	for (auto &model_mapping : model_map) {
		auto percented_size = model_mapping.second->get_size() * f_size / size;
		model_mapping.second->set_size(percented_size);
	}

	size = f_size;
}

void cw::composition::animated_actor::set_alpha(const float& f_alpha){
	alpha = f_alpha;
	for(auto& model : model_map){
		for(auto& sprite : model.second->get_animations()){
			for(auto& frame : sprite.second->frames){
				for(auto& vertex : frame->get_vertices()){
					vertex.set_alpha(alpha);
				}
			}
		}
	}
}

void cw::composition::animated_actor::update(const float& dt){
	for(auto& model_mapping : model_map){
		model_mapping.second->update(dt);
	}

	logic(dt);
}

void cw::composition::animated_actor::add_model(const std::string& model_name,
												const glm::vec3& origin,
												const glm::vec3& size,
												const std::string& template_file){

	if(model_map.find(model_name) == model_map.end()){
		model_map[model_name] = core->video->load_model(origin,
				size,
				core->filesystem->get_file_path(template_file));

	} else {
		throw std::runtime_error(model_name + " already exists, remove it first before adding one with the same name");
	}

}

std::shared_ptr<cw::graphical::object::model> 
cw::composition::animated_actor::get_model(const std::string& model_name){
	if(model_map.find(model_name) != model_map.end()){
		return model_map[model_name];
	} else {
		throw std::runtime_error(model_name + " does not exist");
	}
}

void cw::composition::animated_actor::remove_model(const std::string& model_name){
	if(model_map.find(model_name) != model_map.end()){
		model_map.erase(model_name);
	} else {
		throw std::runtime_error(model_name + " does not exist or was already removed");
	}
}

void cw::composition::animated_actor::add_rigid_body(const std::string& body_name,
													 const glm::vec3& origin,
													 const glm::vec3& size,
													 const float& mass){

	if(body_map.find(body_name) == body_map.end()){
		body_map[body_name]  = core->physics->create_primitive(simulation::physics::PRIMITIVE_PROXY::BOX,
				                                               origin,
				                                               size,
				                                               mass);

		body_map[body_name]->physic_body->setUserPointer(this);

	} else {
		throw std::runtime_error(body_name + " already exists, remove it first before adding one with the same name");
	}

}

auto cw::composition::animated_actor::get_rigid_body(const std::string& body_name){

	if(body_map.find(body_name) != body_map.end()){
		return body_map[body_name];
	} else {
		throw std::runtime_error(body_name + " does not exist");
	}

}

void cw::composition::animated_actor::remove_rigid_body(const std::string& body_name){

	if(body_map.find(body_name) != body_map.end()){
		core->physics->remove_rigid_body(body_map[body_name]);
		body_map.erase(body_name);
	} else {
		throw std::runtime_error(body_name + " does not exist or was already removed");
	}

}

void cw::composition::animated_actor::add_character(const std::string& character_name,
													const glm::vec3& origin,
													const glm::vec2& size,
													const float& step_height){

	if(character_map.find(character_name) == character_map.end()){
		character_map[character_name]  = core->physics->create_character(origin, size, step_height);
		static_cast<btKinematicCharacterController*>(character_map[character_name]->get_character_object())->
				getGhostObject()->setUserPointer(this);
	} else {
		throw std::runtime_error(character_name + " already exists, remove it first before adding one with the same name");
	}

}

auto cw::composition::animated_actor::get_character(const std::string& character_name){

	if(character_map.find(character_name) != character_map.end()){
		return character_map[character_name];
	} else {
		throw std::runtime_error(character_name + " does not exist");
	}

}

void cw::composition::animated_actor::remove_character(const std::string& character_name){

	if(character_map.find(character_name) != character_map.end()){
		  core->physics->remove_character(character_map[character_name]);
		character_map.erase(character_name);
	} else {
		throw std::runtime_error(character_name + " does not exist or was already removed");
	}

}

std::map<std::string, std::shared_ptr<cw::graphical::object::renderable> >
cw::composition::animated_actor::get_model_map(){
    std::map<std::string, std::shared_ptr<cw::graphical::object::renderable> > mmap;

    for(auto mapping : this->model_map){
        mmap[mapping.first] = mapping.second;
    }

	return mmap;
}