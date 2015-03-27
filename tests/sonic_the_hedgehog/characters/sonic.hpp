#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/actor.hpp>

namespace game{
namespace characters{
	
	class sonic;

}// namespace characters
}// namespace game

class game::characters::sonic: public cw::interface::composition::actor{
public:
	sonic(){

	}

	virtual void init(){

		add_model("sonic_model", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(40.0f, 42.0f, 0.0f), "sonic.json");
		add_character("sonic_character", glm::vec3(0, 80, 0), glm::vec2(26, 24), 0.35f);

	}

	virtual void deinit(){

	}

	virtual void logic(const float& dt){

		if(core->input->is_key_down("k")){
			get_model("sonic_model")->change_animation("walk");
		}

	}


//	model_map models;
//	std::shared_ptr<core> core;

};