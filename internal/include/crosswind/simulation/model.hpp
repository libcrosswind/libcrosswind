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

#include <iostream>


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

	virtual void storage_to_render(const std::string& sprite_name){
		sprites[sprite_name] = sprite_storage[sprite_name];
		sprite_storage.erase(sprite_name);
	}

	virtual void render_to_storage(const std::string& sprite_name){
		sprite_storage[sprite_name] = sprites[sprite_name];
		sprites.erase(sprite_name);
	}

    virtual void constrain(const std::string& sprite, 
    	             	   const std::string& body, 
    	             	   const glm::vec3& offset = glm::vec3(0.0f, 0.0f, 0.0f)){

    	constrained_bodies[sprite] = body;

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
	            
				glm::vec3 b_origin(rigid_bodies[constrain_mapping.second]->get_origin().x,
								   rigid_bodies[constrain_mapping.second]->get_origin().y,
						           rigid_bodies[constrain_mapping.second]->get_origin().z);

				sprites[constrain_mapping.first]->set_origin(b_origin);
			std::cout << b_origin.y << std::endl;
			}

	}

	
//	std::map<std::string, glm::vec3> offsets;
//	glm::vec3 origin;

public:
	std::map<std::string, std::shared_ptr<sprite> > sprites;

	std::map<std::string, std::shared_ptr<physics::detail::rigid_body> > rigid_bodies;
	std::map<std::string, std::string> constrained_bodies;

private:
	std::map<std::string, std::shared_ptr<sprite> > sprite_storage;
};// class model