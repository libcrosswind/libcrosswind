#pragma once

#include <map>
#include <crosswind/simulation/sprite.hpp>
#include <crosswind/simulation/detail/standard_actor.hpp>
#include <crosswind/physics/detail/rigid_body.hpp>

namespace cw{
namespace simulation{

	class model;

}// namespace simulation
}// namespace cw


class cw::simulation::model: public cw::simulation::detail::standard_actor{
public:
	model(/*const glm::vec3 o*/)/*: origin(o)*/{
	}


    virtual void add_sprite(const std::string& sprite_name, 
    						std::shared_ptr<sprite> sprite){
    	sprites[sprite_name] = sprite;
    }

    virtual void add_body(const std::string& body_name, 
						  std::shared_ptr<physics::detail::rigid_body> body){
		
		glm::vec3 b_origin(body->get_origin().x, 
						   body->get_origin().y, 
						   body->get_origin().z);

//		glm::vec3 offset = origin - b_origin;

//		rigid_body = body;
//		offsets[body->name] = offset;
		rigid_bodies[body_name] = body;
    }


    virtual void constrain(const std::string& sprite, 
    	             	   const std::string& body, 
    	             	   const glm::vec3& offset = glm::vec3(0.0f, 0.0f, 0.0f)){


    	constrained_bodies[sprites[sprite]] = rigid_bodies[body];

    }	

	virtual void update(double delta){

		for(auto& constrain_mapping : constrained_bodies){
/*
            std::cout << "mapping: " << constrain_mapping.first << " " <<
            			 sprites.second->get_origin().x << " " << 
            			 sprites.second->get_origin().y << " " << 
            			 sprites.second->get_origin().z
            << std::endl;*/
	            
				glm::vec3 b_origin(constrain_mapping.second->get_origin().x, 
						 		   constrain_mapping.second->get_origin().y, 
								   constrain_mapping.second->get_origin().z);


				constrain_mapping.first->set_origin(b_origin);
			}
		}

	
//	std::map<std::string, glm::vec3> offsets;
//	glm::vec3 origin;

public:
	std::map<std::string, std::shared_ptr<sprite> > sprites;
	std::map<std::string, std::shared_ptr<physics::detail::rigid_body> > rigid_bodies;

	std::map<std::shared_ptr<sprite>, 
	         std::shared_ptr<physics::detail::rigid_body> > constrained_bodies;
};// class model