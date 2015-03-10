#pragma once

#include <map>
#include <crosswind/simulation/sprite.hpp>
#include <crosswind/simulation/detail/standard_actor.hpp>
#include <crosswind/physics/detail/rigid_body.hpp>

namespace cw{
namespace simulation{

	class actor;

}// namespace simulation
}// namespace cw

#include <iostream>

class cw::simulation::actor: public cw::simulation::detail::standard_actor{
public:
	actor(){
		frame_counter = 0;
	}


	virtual void update(double delta){

			if(frame_counter++ == 50){
            std::cout << "rigid_body: " << 
            			 rigid_body->get_position().x << " " << 
            			 rigid_body->get_position().y << " " << 
            			 rigid_body->get_position().z
            << std::endl;
				frame_counter = 0;
			}

			for(auto& sprite_mapping : sprites){

				//auto p = rigid_body->get_position();
				//p.y = -p.y;
				sprite_mapping.second->set_position(sprite_mapping.second->get_position());
			}

	}


	int frame_counter;
	std::map<std::string, std::shared_ptr<sprite> > sprites;
	std::shared_ptr<physics::detail::rigid_body> rigid_body;
};