#include <memory>
#include <string>
#include <stdexcept>

#include "glm/glm.hpp"

#include "crosswind/composition/actor.hpp"
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

cw::composition::actor::actor(){

}

cw::composition::actor::~actor(){

	for(auto& body_mapping: body_map){
		core->physics->remove_rigid_body(body_mapping.second);
	}

	for(auto& character_mapping: character_map){
		core->physics->remove_character(character_mapping.second);
	}
}

void cw::composition::actor::set_origin(const glm::vec3& f_origin){
	for (auto &model : model_map) {
		auto translated_origin = model.second->get_origin() + f_origin - origin;
		model.second->set_origin(translated_origin);
	}

	for (auto &text : text_map) {
		auto translated_origin = text.second->get_origin() + f_origin - origin;
		text.second->set_origin(translated_origin);
	}

	origin = f_origin;
}

void cw::composition::actor::set_size(const glm::vec3& f_size){
	for (auto &model : model_map) {
		auto percented_size = model.second->get_size() * f_size / size;
		model.second->set_size(percented_size);
	}

	size = f_size;
}

void cw::composition::actor::set_alpha(const float& f_alpha){
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

void cw::composition::actor::update(const float& dt){
	for(auto& model_mapping : model_map){
		model_mapping.second->update(dt);
	}

	logic(dt);
}

void cw::composition::actor::add_text(const std::string& text_name,
									  const std::string& text,
									  const glm::vec3& origin,
									  const glm::vec3& color,
									  const int& size,
									  const std::string& font_path){

	if(text_map.find(name + "_" + text_name) == text_map.end()){
		text_map[name + "_" + text_name] = core->video->load_text(name + "_" + text_name,
													 text,
													 origin,
													 color,
													 size,
													 core->filesystem->get_file_path(font_path));

	} else {
		throw std::runtime_error(name + "_" + text_name + " already exists, remove it first before adding one with the same name");
	}
}

std::shared_ptr<cw::graphical::object::text> cw::composition::actor::get_text(const std::string& text_name){
	if(text_map.find(name + "_" + text_name) != text_map.end()){
		return text_map[name + "_" + text_name];
	} else {
		throw std::runtime_error(name + "_" + text_name + " does not exist");
	}
}

void cw::composition::actor::remove_text(const std::string& text_name){
	if(text_map.find(name + "_" + text_name) != text_map.end()){
		text_map.erase(name + "_" + text_name);
	} else {
		throw std::runtime_error(name + "_" + text_name + " does not exist or was already removed");
	}
}

void cw::composition::actor::add_model(const std::string& model_name,
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

std::shared_ptr<cw::graphical::object::model> cw::composition::actor::get_model(const std::string& model_name){
	if(model_map.find(model_name) != model_map.end()){
		return model_map[model_name];
	} else {
		throw std::runtime_error(model_name + " does not exist");
	}
}

void cw::composition::actor::remove_model(const std::string& model_name){
	if(model_map.find(model_name) != model_map.end()){
		model_map.erase(model_name);
	} else {
		throw std::runtime_error(model_name + " does not exist or was already removed");
	}
}

void cw::composition::actor::add_rigid_body(const std::string& body_name,
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

auto cw::composition::actor::get_rigid_body(const std::string& body_name){

	if(body_map.find(body_name) != body_map.end()){
		return body_map[body_name];
	} else {
		throw std::runtime_error(body_name + " does not exist");
	}

}

void cw::composition::actor::remove_rigid_body(const std::string& body_name){

	if(body_map.find(body_name) != body_map.end()){
		core->physics->remove_rigid_body(body_map[body_name]);
		body_map.erase(body_name);
	} else {
		throw std::runtime_error(body_name + " does not exist or was already removed");
	}

}

void cw::composition::actor::add_character(const std::string& character_name,
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

auto cw::composition::actor::get_character(const std::string& character_name){

	if(character_map.find(character_name) != character_map.end()){
		return character_map[character_name];
	} else {
		throw std::runtime_error(character_name + " does not exist");
	}

}

void cw::composition::actor::remove_character(const std::string& character_name){

	if(character_map.find(character_name) != character_map.end()){
		  core->physics->remove_character(character_map[character_name]);
		character_map.erase(character_name);
	} else {
		throw std::runtime_error(character_name + " does not exist or was already removed");
	}

}

std::map<std::string, std::shared_ptr<cw::graphical::object::model> >& cw::composition::actor::get_model_map(){
	return model_map;
}

std::map<std::string, std::shared_ptr<cw::graphical::object::text> >& cw::composition::actor::get_text_map(){
	return text_map;
}
