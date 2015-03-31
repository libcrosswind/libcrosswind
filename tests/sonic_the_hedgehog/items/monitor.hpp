#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/actor.hpp>

namespace game{
namespace items{
	
	class monitor;

}// namespace items
}// namespace game

class game::items::monitor: public cw::interface::composition::actor{
public:
	monitor(){

	}

	virtual void init(){

		this->add_model("sonic_monitor", 
			            glm::vec3(0.0f, 0.0f, 0.0f), 
			            glm::vec3(30.0f, 30.0f, 0.0f), "monitors.json");

		this->add_rigid_body("sonic_monitor",
							 glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(30.0f, 30.0f, 10.0f), 1.0f);

		this->conditions["broken"] = false;
	}

	virtual void deinit(){

	}

	void destroy(){
		this->conditions["broken"] = true;
		this->remove_rigid_body("sonic_monitor");
	}

	void set_content(const std::string& content){
		this->get_model("monitor")->change_animation(content);
	}

	virtual void logic(const float& dt){

		if(this->conditions["broken"]){
			this->get_model("monitor")->change_animation("monitor_broken");
		}

	}

};// class sonic_monitor