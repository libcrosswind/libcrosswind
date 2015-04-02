#pragma once

#include <glm/glm.hpp>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/actor.hpp>

namespace game {
namespace characters {
namespace title{

	class title_background;

}// namespace title
}// namespace characters
}// namespace game

class game::characters::title::title_background: public cw::interface::composition::actor{
public:

	title_background(){

	}

	virtual void init(){

		auto window_size = core->video->window->get_size();

		this->add_model("gh_background",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
				"gh_background.json");

		this->add_model("gh_background_water",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
				"gh_background_water.json");


	}

	virtual void deinit(){

	}

	virtual void logic(const float& delta){

	}

};