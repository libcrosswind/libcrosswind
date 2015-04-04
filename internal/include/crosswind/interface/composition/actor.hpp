#pragma once

#include <map>
#include <memory>
#include <string>
#include <functional>

#include <crosswind/interface/graphical/object/model.hpp>
#include <crosswind/interface/simulation/detail/character.hpp>
#include <crosswind/interface/simulation/detail/body.hpp>

namespace cw{
namespace interface{
namespace composition{

	class actor;

}// namespace composition
}// namespace interface
}// namespace cw

class cw::interface::composition::actor: public std::enable_shared_from_this<cw::interface::composition::actor>{
	typedef std::map<std::string, std::shared_ptr<graphical::object::model> >       model_map;
	typedef std::map<std::string, std::shared_ptr<simulation::detail::body> >       body_map;
	typedef std::map<std::string, std::shared_ptr<simulation::detail::character> >  character_map;
public:
	actor(): name("undefined"){
		alpha = 1.0f;
	}

	virtual ~actor(){

		for(auto& body_mapping: bodies){
			core->physics->remove_rigid_body(body_mapping.second);
		}

		for(auto& character_mapping: characters){
			core->physics->remove_character(character_mapping.second);
		}
	}

	void set_init(const std::function<void()>& fun){
		init = fun;
	}

	void set_deinit(const std::function<void()>& fun){
		deinit = fun;
	}

	void set_logic(const std::function<void(const float&)>& fun){
		logic = fun;
	}

	std::function<void()> init;
	std::function<void()> deinit;
	std::function<void(const float&)> logic;

	virtual void set_name(const std::string& f_name){
		name = f_name;
	}

	virtual std::string& get_name(){
		return name;
	}

	virtual void set_alpha(const float& f_alpha){
		alpha = f_alpha;
		for(auto& model : models){
			for(auto& sprite : model.second->get_animations()){

				for(auto& frame : sprite.second->frames){
					for(auto& vertex : frame->get_vertices()){
						vertex.set_alpha(alpha);
					}
				}
			}
		}
	}

	virtual float& get_alpha(){
		return alpha;
	}

	virtual void update(const float& dt){
		for(auto& model_mapping : models){
			model_mapping.second->update(dt);
		}
		logic(dt);

	}



	virtual void add_model(const std::string& model_name,
			               const glm::vec3& origin,
			               const glm::vec3& size,
	                       const std::string& template_file){

		if(models.find(model_name) == models.end()){
			models[model_name] = core->video->load_model(origin,
					size,
					core->filesystem->get_file_path(template_file));
		} else {
			throw std::runtime_error(model_name + " already exists, remove it first before adding one with the same name");
		}

	}

	virtual std::shared_ptr<graphical::object::model> get_model(const std::string& model_name){
		if(models.find(model_name) != models.end()){
			return models[model_name];
		} else {
			throw std::runtime_error(model_name + " does not exist");
		}
	}

	virtual void remove_model(const std::string& model_name){
		if(models.find(model_name) != models.end()){
			models.erase(model_name);
		} else {
			throw std::runtime_error(model_name + " does not exist or was already removed");
		}
	}

	void add_rigid_body(const std::string& body_name,
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

	virtual std::shared_ptr<simulation::detail::body> get_rigid_body(const std::string& body_name){

		if(bodies.find(body_name) != bodies.end()){
			return bodies[body_name];
		} else {
			throw std::runtime_error(body_name + " does not exist");
		}

	}

	virtual void remove_rigid_body(const std::string& body_name){

		if(bodies.find(body_name) != bodies.end()){
			core->physics->remove_rigid_body(bodies[body_name]);
			bodies.erase(body_name);
		} else {
			throw std::runtime_error(body_name + " does not exist or was already removed");
		}

	}

	virtual void add_character(const std::string& character_name,
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

	virtual std::shared_ptr<simulation::detail::character> get_character(const std::string& character_name){

		if(characters.find(character_name) != characters.end()){
			return characters[character_name];
		} else {
			throw std::runtime_error(character_name + " does not exist");
		}

	}

	virtual void remove_character(const std::string& character_name){

		if(characters.find(character_name) != characters.end()){
			  core->physics->remove_character(characters[character_name]);
			  characters.erase(character_name);
		} else {
			throw std::runtime_error(character_name + " does not exist or was already removed");
		}

	}

	virtual model_map& get_model_map(){
		return models;
	}

	std::shared_ptr<core> core;
	std::map<std::string, bool> conditions;

private:
	model_map       models;
	body_map        bodies;
	character_map   characters;

	std::string name;
	glm::vec3 size;
	float alpha;

};// class actor