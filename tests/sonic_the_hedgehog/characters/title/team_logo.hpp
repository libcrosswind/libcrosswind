#pragma once

#include "glm/glm.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/composition/actor.hpp"

namespace game {
namespace characters {
namespace title{

	class team_logo;

}// namespace title
}// namespace characters
}// namespace game

class game::characters::title::team_logo: public cw::composition::actor{
public:

	team_logo(){

	}

	virtual void init(){

		auto window_size = core->video->window->get_size();

		const float x_scale = window_size.x / 1920.0f;
		const float y_scale = window_size.y / 1080.0f;


		this->add_model("team_logo",
				        glm::vec3(0.0f, 0.0f, 0.0f),
				        glm::vec3(-100.0f * x_scale, -100.0f * y_scale, 0.0f),
				        "team_logo.json");

	}

	virtual void deinit(){

	}

	virtual void logic(const float& delta){

	}

};