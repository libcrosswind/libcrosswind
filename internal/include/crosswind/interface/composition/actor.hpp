#pragma once

#include <map>
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

	virtual void update(const float& dt){

	}

	virtual model_map& get_model_map(){
		return models;
	}


protected:
	model_map models;
};// class actor