#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/actor.hpp>

namespace game{
namespace characters{
	
	class chunk;

}// namespace characters
}// namespace game

class game::characters::chunk: public cw::interface::composition::actor{
public:
	chunk(){

	}


	virtual void init(){
/*
		glm::vec3 ground_offset = glm::vec3(0.0f, 0.0f, 0.0f);
		ground_offset.y = -96.0f;

		add_rigid_body("ground_body", ground_offset, glm::vec3(256.0f, 64.0f, 10.0f), 0.0f);
		load_models(templates, positions, sizes);*/

	}

	virtual void deinit(){

	}


	virtual void logic(const float& dt){

/*		if(core->input->is_key_down("k")){
			get_model("sonic_model")->change_animation("walk");
		}
*/
	}


protected:

	void load_models(const std::vector<std::string>& model_vector,
			const std::vector<glm::vec3>& positions,
			const std::vector<glm::vec3>& sizes){

		for(int i = 0; i<model_vector.size(); ++i){
			add_model("model_" + std::to_string(i), positions[i], sizes[i], model_vector[i]);
		}

	}

};