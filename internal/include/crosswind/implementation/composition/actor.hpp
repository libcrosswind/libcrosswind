#pragma once

#include <memory>

#include <glm/glm.hpp>

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
		models["sonic_model"] = core->video->load_model(glm::vec3(0.0f, 0.0f, 0.0f),
				                                        glm::vec3(40.0f, 42.0f, 0.0f),
				                                        core->filesystem->get_file_path("sonic.json"));
	}

	virtual void deinit(){

	}

	virtual void logic(const float& dt){

	}


//	model_map models;
//	std::shared_ptr<core> core;

};