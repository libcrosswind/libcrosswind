#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/composition/actor/animated_actor.hpp"

namespace game{
namespace items{
	
	class monitor;

}// namespace items
}// namespace game

class game::items::monitor: public cw::composition::animated_actor{
public:
	monitor(): animated_actor("monitor"){

	}

	virtual void init(){

		this->add_model("monitor",
			            glm::vec3(40.0f, 0.0f, 0.0f),
			            glm::vec3(30.0f, 30.0f, 0.0f), "monitors.json");

		this->add_rigid_body("monitor",
							 glm::vec3(40.0f, 0.0f, 0.0f), glm::vec3(30.0f, 30.0f, 5.0f), 1.0f);

		//this->get_rigid_body("monitor")->set_activation_policy(DISABLE_DEACTIVATION);
		//this->get_rigid_body("monitor")->set_linear_factor(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));


		//this->conditions["broken"] = false;
	}

	virtual void deinit(){

	}

	void destroy(){


		this->get_model("monitor")->change_animation("monitor_broken");
		update(1.0f/60.0f);

		//this->conditions["broken"] = true;
		this->remove_rigid_body("monitor");

	}

	void set_content(const std::string& content){
		this->get_model("monitor")->change_animation(content);
	}

	/*void map_positions(){

		glm::vec3 b_origin(this->get_rigid_body("monitor")->get_origin().x,
				this->get_rigid_body("monitor")->get_origin().y,
				this->get_rigid_body("monitor")->get_origin().z);
		this->get_model("monitor")->get_render_sprite_list()["current"]->set_origin(b_origin);

	}*/

	virtual void logic(const float& dt){

		//if(!this->conditions["broken"]) {
			//map_positions();

		//}

	}

};// class sonic_monitor