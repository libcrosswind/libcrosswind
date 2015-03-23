#pragma once

#include <map>
#include <memory>
#include <string>

#include <crosswind/interface/graphical/object/model.hpp>

namespace cw{
namespace interface{
namespace composition{

	class actor;

}// namespace composition
}// namespace interface
}// namespace cw

class cw::interface::composition::actor{
	typedef std::map<std::string, std::shared_ptr<interface::graphical::object::model> > model_map;
public:
	actor(){

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

	virtual model_map& get_model_map(){
		return models;
	}

	std::shared_ptr<core> core;

protected:
	model_map models;
};// class actor