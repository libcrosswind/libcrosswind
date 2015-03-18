#pragma once

#include <map>
#include <crosswind/physics/detail/rigid_body.hpp>
#include <crosswind/simulation/sprite.hpp>
#include <crosswind/simulation/detail/standard_actor.hpp>
#include <crosswind/simulation/sprite_animation.hpp>

namespace cw{
namespace simulation{

	class model;

}// namespace simulation
}// namespace cw


class cw::simulation::model: public cw::simulation::detail::standard_actor{
public:
	model(){

	}

    virtual void add_body(const std::string& body_name, 
						  std::shared_ptr<physics::detail::rigid_body> body){
		rigid_bodies[body_name] = body;
    }

    virtual void constrain(const std::string& sprite, 
    	             	   const std::string& body, 
    	             	   const glm::vec3& offset = glm::vec3(0.0f, 0.0f, 0.0f)){

    	constrained_bodies[sprite] = body;

    }

	virtual void change_animation(const std::string& new_animation){
		animations["current"] = animations[new_animation];
	}

	virtual void update(double delta){

        delta_count += delta;

		for(auto& constrain_mapping : constrained_bodies){

/*			glm::vec3 b_origin(rigid_bodies[constrain_mapping.second]->get_origin().x,
					rigid_bodies[constrain_mapping.second]->get_origin().y,
					rigid_bodies[constrain_mapping.second]->get_origin().z);

			sprites[constrain_mapping.first]->set_origin(b_origin);*/
		}


        if(delta_count >= animations["current"]->duration / animations["current"]->frames.size()){

            delta_count = 0;

	        animations["current"]->current_frame++;

            if(animations["current"]->current_frame >= animations["current"]->frames.size()){
	            animations["current"]->current_frame = 0;
            }
        }

		render_sprite_list["current"] = animations["current"]->frames[animations["current"]->current_frame];


	}

	auto& get_render_sprite_list(){
		return render_sprite_list;
	}

	auto& get_animations(){
		return animations;
	}

private:
	std::map<std::string, std::shared_ptr<sprite> > render_sprite_list;
	std::map<std::string, std::shared_ptr<physics::detail::rigid_body> > rigid_bodies;
	std::map<std::string, std::string> constrained_bodies;

	std::map<std::string, std::shared_ptr<sprite_animation> > animations;
};// class model