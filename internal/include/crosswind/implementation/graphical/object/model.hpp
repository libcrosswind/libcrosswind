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

	virtual void change_animation(const std::string& new_animation, const bool& x_orientation = true){

		animations["current"] = animations[new_animation];
		animations["current"]->flip(x_orientation);

	}

	virtual void update(const float& delta){

        delta_count += delta;

        if(delta_count >= animations["current"]->duration / (float) animations["current"]->frames.size()){

            delta_count = 0;

	        animations["current"]->current_frame++;

            if(animations["current"]->current_frame >= animations["current"]->frames.size()){
	            animations["current"]->current_frame = 0;
            }
        }

		render_sprite_list["current"] = animations["current"]->frames[animations["current"]->current_frame];

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
		for(auto& animation : animations){
			for(auto& frame : animation.second->frames){
				frame->set_origin(origin);
			}
		}
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

};// class model