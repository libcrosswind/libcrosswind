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
	model(): origin(0.0f, 0.0f, 0.0f){

	}

    virtual void attach_rigid_body(const std::string& body_name,
						           std::shared_ptr<physics::detail::rigid_body> body,
                                   const bool& synchronize = false){

		rigid_bodies[body_name] = body;

	    if(synchronize){
		    attached_bodies[body_name] = rigid_bodies[body_name];
	    }
    }


	virtual void change_animation(const std::string& new_animation, const bool& flip = false){
		animations["current"] = animations[new_animation];
/*		if(flip){

			for(auto& sprite : animations["current"]->frames){
				sprite->
			}

		}*/
	}

	virtual void update(double delta){

        delta_count += delta;

        if(delta_count >= animations["current"]->duration / animations["current"]->frames.size()){

            delta_count = 0;

	        animations["current"]->current_frame++;

            if(animations["current"]->current_frame >= animations["current"]->frames.size()){
	            animations["current"]->current_frame = 0;
            }
        }

		render_sprite_list["current"] = animations["current"]->frames[animations["current"]->current_frame];

		for(auto& mapping : attached_bodies){

			glm::vec3 b_origin(mapping.second->get_origin().x,
					mapping.second->get_origin().y,
					mapping.second->get_origin().z);

			render_sprite_list["current"]->set_origin(b_origin);
		}
	}

	auto& get_render_sprite_list(){
		return render_sprite_list;
	}

	auto& get_animations(){
		return animations;
	}

	void set_origin(const glm::vec3& o){
		origin = o;
	}

	auto get_origin(){
		return origin;
	}

	void set_size(const glm::vec3& s){
		size = s;
	}

	auto get_size(){
		return size;
	}

private:
	glm::vec3 origin;
	glm::vec3 size;

	std::map<std::string, std::shared_ptr<sprite> > render_sprite_list;
	std::map<std::string, std::shared_ptr<sprite_animation> > animations;
	std::map<std::string, std::shared_ptr<physics::detail::rigid_body> > rigid_bodies;
	std::map<std::string, std::shared_ptr<physics::detail::rigid_body> > attached_bodies;

};// class model