#pragma once

#include <memory>
#include <vector>
#include <string>

#include "glm/glm.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/composition/actor/animated_actor.hpp"

namespace game{
namespace characters{
	
	class chunk;

}// namespace characters
}// namespace game

class game::characters::chunk: public cw::composition::animated_actor{
public:
	chunk(): animated_actor("chunk"){

	}

	void set_origin(const glm::vec3& f_origin){
		origin = f_origin;
	}

	glm::vec3 get_origin(){
		return origin;
	}

	//Relative to chunk's origin
	void add_models(const std::vector<std::string>& model_templates,
					const std::vector<glm::vec3>& model_positions,
					const std::vector<glm::vec3>& model_sizes){

		for(int i = 0; i<model_templates.size(); ++i){

			glm::vec3 model_offset = origin;
			model_offset += model_positions[i];

			add_model("model_" + std::to_string(i), model_offset, model_sizes[i], model_templates[i]);
		}

	}

	//Relative to chunk's origin
	void add_rigid_bodies(const std::vector<glm::vec3>& body_positions,
						  const std::vector<glm::vec3>& body_sizes){

		for(int i = 0; i<body_positions.size(); ++i){

			glm::vec3 body_offset = origin;
			body_offset += body_positions[i];

			add_rigid_body("body_" + std::to_string(i), body_offset, body_sizes[i], /*glm::vec3(256.0f, 64.0f, 10.0f),*/ 0.0f);
		}

	}

	virtual void init(){
/*

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

	glm::vec3 origin;

};