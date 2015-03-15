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

    virtual void constrain(const std::string& body, 
    					   const std::vector<glm::vec2>& position_clamp){

    	constrained_positions[body] = position_clamp;

    }


	virtual void update(double delta){

/*        delta_count += delta;

        auto& a = animations.data.acquire();

        if(delta_count >= a["current"]->duration / a["current"]->frames.size()){

            delta_count = 0;

            a["current"]->current_frame++;

            if(a["current"]->current_frame >= a["current"]->frames.size()){
                a["current"]->current_frame = 0;
            }
        }

        swap_graphical_item(sprites, "current", a["current"]->frames[a["current"]->current_frame]);

        animations.data.release();
*/

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

		for(auto& constrain_mapping : constrained_positions){

/*			glm::vec3 b_origin(rigid_bodies[constrain_mapping.first]->get_origin().x,
					 		   rigid_bodies[constrain_mapping.first]->get_origin().y, 
							   rigid_bodies[constrain_mapping.first]->get_origin().z);


			auto c_xmin = constrained_positions[constrain_mapping.first][0][0];
			auto c_xmax = constrained_positions[constrain_mapping.first][0][1];			

			auto c_ymin = constrained_positions[constrain_mapping.first][1][0];
			auto c_ymax = constrained_positions[constrain_mapping.first][1][1];			

			auto c_zmin = constrained_positions[constrain_mapping.first][2][0];
			auto c_zmax = constrained_positions[constrain_mapping.first][2][1];			

			glm::vec3 c_origin(glm::clamp(b_origin.x, c_xmin, c_xmax),
							   glm::clamp(b_origin.y, c_ymin, c_ymax),
							   glm::clamp(b_origin.z, c_zmin, c_zmax));

			c_origin.x = 0.0f;
			c_origin.y = 0.0f;
			c_origin.z = 0.0f;

			std::cout << constrain_mapping.first << std::endl;

			rigid_bodies[constrain_mapping.first]->set_origin(c_origin);*/
		}	
	}

	
//	std::map<std::string, glm::vec3> offsets;
//	glm::vec3 origin;

public:
	std::map<std::string, std::shared_ptr<sprite> > sprites;
	std::map<std::string, std::shared_ptr<physics::detail::rigid_body> > rigid_bodies;

	std::map<std::shared_ptr<sprite>, 
	         std::shared_ptr<physics::detail::rigid_body> > constrained_bodies;

   	std::map<std::string, std::vector<glm::vec2> > constrained_positions;

};// class model