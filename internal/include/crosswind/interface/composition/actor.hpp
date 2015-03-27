#pragma once

#include <map>
#include <memory>
#include <string>

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

class cw::interface::composition::actor{
	typedef std::map<std::string, std::shared_ptr<graphical::object::model> >       model_map;
	typedef std::map<std::string, std::shared_ptr<simulation::detail::body> >       body_map;
	typedef std::map<std::string, std::shared_ptr<simulation::detail::character> >  character_map;
public:
	actor(){

	}

	virtual ~actor(){
		for(auto character_mapping: characters){
			core->physics->remove_character(character_mapping.second);
		}
	}

	virtual void init() = 0;
	virtual void deinit() = 0;

	virtual void update(const float& dt){
		logic(dt);

		for(auto& model_mapping : models){
			model_mapping.second->update(dt);
		}

	}

	virtual void logic(const float& dt) = 0;


	virtual void add_model(){

	}

	virtual void remove_model(){

	}

	virtual void add_character(const std::string& name,
							   const glm::vec3& origin,
							   const glm::vec2& size,
			                   const float& step_height){

		if(characters.find(name) == characters.end()){
			characters[name]  = core->physics->create_character(origin, size, step_height);
		} else {
			throw std::runtime_error(name + " already exists, remove it first before adding one with the same name");
		}

	}

	virtual void remove_character(const std::string& name){

		if(characters.find(name) != characters.end()){
			  core->physics->remove_character(characters[name]);
		} else {
			throw std::runtime_error(name + " does not exist or was already removed");
		}

	}

	virtual model_map& get_model_map(){
		return models;
	}

	std::shared_ptr<core> core;

protected:
	model_map       models;
	body_map        bodies;
	character_map   characters;
};// class actor