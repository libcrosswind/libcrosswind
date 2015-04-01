#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/actor.hpp>

namespace game {
namespace characters {
namespace title{

	class sega_logo;

}// namespace title
}// namespace characters
}// namespace game

class game::characters::title::sega_logo: public cw::interface::composition::actor{
public:

	sega_logo(){

	}

	virtual void init(){

		auto window_size = core->video->window->get_size();

		this->add_model("sega_logo",
				        glm::vec3(0.0f, 0.0f, 0.0f),
				        glm::vec3(120.0f, 60.0f, 0.0f),
				        "sega_logo.json");

	}

	virtual void deinit(){

	}

	virtual void logic(const float& delta){

	}

};