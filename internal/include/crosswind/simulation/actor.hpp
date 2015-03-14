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

/*		positions["main"] = glm::vec3(10.0f, 10.0f, 10.0f); //Origin
		positions["main"] = glm::vec3(5.0f, 5.0f, 5.0f); //Offset

		positions["main"] = glm::vec3(10.0f, 10.0f, 10.0f); //Origin
		*/

	}

    virtual void add_body(std::shared_ptr<physics::detail::rigid_body> body){
        btCompoundShape* B= new btCompoundShape();

    }

	virtual void update(double delta){

			if(frame_counter++ >= 0){
            std::cout << "rigid_body: " << 
            			 rigid_body->get_origin().x << " " << 
            			 rigid_body->get_origin().y << " " << 
            			 rigid_body->get_origin().z
            << std::endl;
				frame_counter = 0;

			for(auto& sprite_mapping : sprites){

            std::cout << "mapping: " << sprite_mapping.first << " " <<
            			 sprite_mapping.second->get_origin().x << " " << 
            			 sprite_mapping.second->get_origin().y << " " << 
            			 sprite_mapping.second->get_origin().z
            << std::endl;

				sprite_mapping.second->set_origin(rigid_body->get_origin());
			}
		}

	}

	std::map<std::string, glm::vec3> positions;

	int frame_counter;
	std::map<std::string, std::shared_ptr<sprite> > sprites;
	std::shared_ptr<physics::detail::rigid_body> rigid_body;
};