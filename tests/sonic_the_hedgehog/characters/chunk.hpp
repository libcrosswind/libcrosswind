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
	chunk(const std::vector<std::string>& c_templates,
			const std::vector<glm::vec3>& c_positions,
			const std::vector<glm::vec3>& c_sizes){

		templates = c_templates;
		positions = c_positions;
		sizes    = c_sizes;
	}

	void load_models(const std::vector<std::string>& model_vector,
			const std::vector<glm::vec3>& positions,
			const std::vector<glm::vec3>& sizes){

		for(int i = 0; i<model_vector.size(); ++i){
			add_model("model_" + std::to_string(i), positions[i], sizes[i], model_vector[i]);
		}

	}

	virtual void init(){

		glm::vec3 ground_offset = glm::vec3(0.0f, 0.0f, 0.0f);
		ground_offset.y = -96.0f;

		add_rigid_body("ground_body", ground_offset, glm::vec3(256.0f, 64.0f, 10.0f), 0.0f);
		load_models(templates, positions, sizes);

	}

	virtual void deinit(){

	}

	virtual void logic(const float& dt){

/*		if(core->input->is_key_down("k")){
			get_model("sonic_model")->change_animation("walk");
		}
*/
	}


//	model_map models;
//	std::shared_ptr<core> core;

	std::vector<std::string> templates;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> sizes;

};