#include "crosswind/graphical/object/sprite_animation.hpp"

cw::graphical::object::sprite_animation::sprite_animation(){

}

cw::graphical::object::sprite_animation::~sprite_animation(){

}

void cw::graphical::object::sprite_animation::set_origin(const glm::vec3& new_origin){
    
    for(auto& frame : frames){
        frame->set_origin(new_origin);
    }

}

void cw::graphical::object::sprite_animation::set_size(const glm::vec3& new_size){

    for(auto& frame : frames){
        frame->set_size(new_size);
    }
    
}