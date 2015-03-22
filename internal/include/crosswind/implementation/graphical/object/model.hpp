#pragma once

#include <map>
//#include <crosswind/physics/detail/rigid_body.hpp>
//#include <crosswind/physics/kinematic_character.hpp>
#include <crosswind/interface/graphical/detail/sprite.hpp>
#include <crosswind/interface/graphical/object/sprite_animation.hpp>
#include <crosswind/interface/graphical/object/model.hpp>

namespace cw{
namespace implementation{
namespace graphical{
namespace object{

	class model;

}// namespace object
}// namespace graphical
}// namespace implementation
}// namespace cw


class cw::implementation::graphical::object::model: public cw::interface::graphical::object::model{
public:
	model(){
	}

/*	virtual void attach_character(const std::string& character_name,
	                              std::shared_ptr<physics::kinematic_character> character,
	                              const bool& synchronize = true){

		characters[character_name] = character;

		if(synchronize){
			attached_characters[character_name] = characters[character_name];
		}

	}*/

/*    virtual void attach_rigid_body(const std::string& body_name,
						           std::shared_ptr<physics::detail::rigid_body> body,
                                   const bool& synchronize = false){

		rigid_bodies[body_name] = body;

	    if(synchronize){
		    attached_bodies[body_name] = rigid_bodies[body_name];
	    }
    }*/

/*	virtual std::map<std::string, std::shared_ptr<physics::detail::rigid_body> > get_rigid_bodies(){
		return rigid_bodies;
	}
*/
	virtual void change_animation(const std::string& new_animation, const bool& x_orientation = true){

		animations["current"] = animations[new_animation];
		animations["current"]->flip(x_orientation);

	}

	virtual void update(float delta){

        delta_count += delta;

        if(delta_count >= animations["current"]->duration / animations["current"]->frames.size()){

            delta_count = 0;

	        animations["current"]->current_frame++;

            if(animations["current"]->current_frame >= animations["current"]->frames.size()){
	            animations["current"]->current_frame = 0;
            }
        }

		render_sprite_list["current"] = animations["current"]->frames[animations["current"]->current_frame];

/*		for(auto& mapping : attached_bodies){

			glm::vec3 b_origin(mapping.second->get_origin().x,
					mapping.second->get_origin().y,
					mapping.second->get_origin().z);

			render_sprite_list["current"]->set_origin(b_origin);
		}

		for(auto& mapping : attached_characters){

			glm::vec3 b_origin(mapping.second->get_origin().x,
					mapping.second->get_origin().y,
					mapping.second->get_origin().z);

			render_sprite_list["current"]->set_origin(b_origin);
		}*/
	}

	virtual std::map<std::string, std::shared_ptr<interface::graphical::detail::sprite> >& get_render_sprite_list(){
		return render_sprite_list;
	}

	virtual void set_animations(std::map<std::string, std::shared_ptr<interface::graphical::object::sprite_animation> >& new_animations){

		animations.clear();

		for(auto mapping : new_animations){
			animations[mapping.first] = mapping.second;
		}
	}

	virtual std::map<std::string, std::shared_ptr<interface::graphical::object::sprite_animation> >& get_animations(){
		return animations;
	}

	virtual void set_origin(const glm::vec3& new_origin){
		origin = new_origin;
	}

	virtual glm::vec3 get_origin(){
		return origin;
	}

	virtual void set_size(const glm::vec3& new_size){
		size = new_size;
	}

	virtual glm::vec3 get_size(){
		return size;
	}

	std::map<std::string, int>  data;

private:
//	std::map<std::string, std::shared_ptr<physics::detail::rigid_body> > rigid_bodies;
//	std::map<std::string, std::shared_ptr<physics::detail::rigid_body> > attached_bodies;

//	std::map<std::string, std::shared_ptr<physics::kinematic_character> > characters;
//	std::map<std::string, std::shared_ptr<physics::kinematic_character> > attached_characters;

};// class model