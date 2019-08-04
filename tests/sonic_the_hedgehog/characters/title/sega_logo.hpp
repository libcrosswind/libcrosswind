#pragma once

#include "glm/glm.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/graphical/video.hpp"
#include "crosswind/graphical/opengl/window.hpp"
#include "crosswind/composition/actor/animated_actor.hpp"

namespace game {
namespace characters {
namespace title{

	class sega_logo;

}// namespace title
}// namespace characters
}// namespace game

class game::characters::title::sega_logo: public cw::composition::animated_actor{
public:

	sega_logo(): animated_actor("sega_logo"){

	}

	virtual void init(){

		auto window_size = core->video->window->get_size();

		this->add_model("sega_logo",
				        glm::vec3(0.0f, 0.0f, 0.0f),
				        glm::vec3(-100.0f * 640.0f/320.0f, -100.0f*480.0f/224.0f, 0.0f),
				        "sega_logo.json");

	}

	virtual void deinit(){

	}

	virtual void logic(const float& delta){

	}

};