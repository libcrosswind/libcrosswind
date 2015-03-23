#pragma once

#include <memory>


#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/actor.hpp>

namespace cw{
namespace implementation{
namespace composition{
	
	class actor;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::implementation::composition::actor: public cw::interface::composition::actor{
public:
	actor(){

	}

	virtual void init(){

	}

	virtual void deinit(){

	}

	virtual void update(const float& dt){

	}


//	model_map models;
//	std::shared_ptr<core> core;

};