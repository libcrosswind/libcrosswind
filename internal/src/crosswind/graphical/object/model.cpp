#include "crosswind/graphical/object/model.hpp"
#include "crosswind/graphical/object/sprite.hpp"
#include "crosswind/graphical/object/sprite_animation.hpp"

cw::graphical::object::model::model(): 
origin(0.0f, 0.0f, 0.0f), 
delta_count(0.0f){

}

void cw::graphical::object::model::change_animation(const std::string& new_animation){

	if(animations["current"] != animations[new_animation]){
		animations["current"] = animations[new_animation];
	}

}

void cw::graphical::object::model::update(const float& delta){

    delta_count += delta;

    if(delta_count >= animations["current"]->duration / (float) animations["current"]->frames.size()){

        delta_count = 0;

        animations["current"]->current_frame++;

        if(animations["current"]->current_frame >= animations["current"]->frames.size()){
            animations["current"]->current_frame = 0;
        }
    }

	set_render_sprite(animations["current"]->frames[animations["current"]->current_frame]);

}

void cw::graphical::object::model::set_render_sprite(auto sprite){

	render_sprite = sprite;

}

auto cw::graphical::object::model::get_render_sprite(){

	return render_sprite;

}

void cw::graphical::object::model::set_animations(const auto& new_animations){

	animations.clear();

	for(auto mapping : new_animations){
		animations[mapping.first] = mapping.second;
	}

}

auto& get_animations(){
	
	return animations;

}

void cw::graphical::object::model::set_origin(const glm::vec3& new_origin){
	
	origin = new_origin;
	for(auto& animation : animations){
		animation.second->set_origin(origin);
	}

}

glm::vec3 cw::graphical::object::model::get_origin(){

	return origin;

}

void cw::graphical::object::model::set_size(const glm::vec3& new_size){

	size = new_size;
	for(auto& animation : animations){
		animation.second->set_size(size);
	}

}

glm::vec3 cw::graphical::object::model::get_size(){

	return size;

}
 