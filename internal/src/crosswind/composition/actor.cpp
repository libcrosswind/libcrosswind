#include <map>
#include <memory>
#include <string>
#include <stdexcept>

#include "glm/glm.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/graphical/object/model.hpp"
#include "crosswind/graphical/object/text.hpp"

#include "crosswind/simulation/detail/character.hpp"
#include "crosswind/simulation/detail/body.hpp"

cw::composition::actor::actor(){

}

cw::composition::actor::~actor(){

	for(auto& body_mapping: bodies){
		core->physics->remove_rigid_body(body_mapping.second);
	}

	for(auto& character_mapping: characters){
		core->physics->remove_character(character_mapping.second);
	}
}

virtual void cw::composition::actor::set_origin(const glm::vec3& f_origin){
	for (auto &model : model_map) {
		auto translated_origin = model.second->get_origin() + f_origin - origin;
		model.second->set_origin(translated_origin);
	}

	origin = f_origin;
}

virtual void cw::composition::actor::set_size(const glm::vec3& f_size){
	for (auto &model : model_map) {
		auto percented_size = model.second->get_size() * f_size / size;
		model.second->set_size(percented_size);
	}

	size = f_size;
}

virtual void cw::composition::actor::set_alpha(const float& f_alpha){
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

	if(text_map.find(text_name) == text_map.end()){
		text_map[text_name] = core->video->load_text(text_name,
													 text,
													 origin,
													 color,
													 size,
													 core->filesystem->get_file_path(font_path));

	} else {
		throw std::runtime_error(text_name + " already exists, remove it first before adding one with the same name");
	}
}

void cw::composition::actor::remove_text(const std::string& text_name){
	if(text_map.find(text_name) != text_map.end()){
		text_map.erase(text_name);
	} else {
		throw std::runtime_error(text_name + " does not exist or was already removed");
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

auto cw::composition::actor::get_model(const std::string& model_name){
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

	if(bodies.find(body_name) == bodies.end()){
		bodies[body_name]  = core->physics->create_primitive(simulation::physics::PRIMITIVE_PROXY::BOX,
				                                             origin,
				                                             size,
				                                             mass);

		bodies[body_name]->physic_body->setUserPointer(this);

	} else {
		throw std::runtime_error(body_name + " already exists, remove it first before adding one with the same name");
	}

}

auto cw::composition::actor::get_rigid_body(const std::string& body_name){

	if(bodies.find(body_name) != bodies.end()){
		return bodies[body_name];
	} else {
		throw std::runtime_error(body_name + " does not exist");
	}

}

void cw::composition::actor::remove_rigid_body(const std::string& body_name){

	if(bodies.find(body_name) != bodies.end()){
		core->physics->remove_rigid_body(bodies[body_name]);
		bodies.erase(body_name);
	} else {
		throw std::runtime_error(body_name + " does not exist or was already removed");
	}

}

void cw::composition::actor::add_character(const std::string& character_name,
				   						   const glm::vec3& origin,
				   						   const glm::vec2& size,
				   					   	   const float& step_height){

	if(characters.find(character_name) == characters.end()){
		characters[character_name]  = core->physics->create_character(origin, size, step_height);
		static_cast<btKinematicCharacterController*>(characters[character_name]->get_character_object())->
				getGhostObject()->setUserPointer(this);
	} else {
		throw std::runtime_error(character_name + " already exists, remove it first before adding one with the same name");
	}

}

auto cw::composition::actor::get_character(const std::string& character_name){

	if(characters.find(character_name) != characters.end()){
		return characters[character_name];
	} else {
		throw std::runtime_error(character_name + " does not exist");
	}

}

void cw::composition::actor::remove_character(const std::string& character_name){

	if(characters.find(character_name) != characters.end()){
		  core->physics->remove_character(characters[character_name]);
		  characters.erase(character_name);
	} else {
		throw std::runtime_error(character_name + " does not exist or was already removed");
	}

}

auto& cw::composition::actor::get_model_map(){
	return model_map;
}

auto& cw::composition::actor::get_text_map(){
	return text_map;
}
