#pragma once

#include <memory>
#include <vector>

#include <crosswind/interface/graphical/detail/sprite.hpp>

namespace cw{
namespace interface{
namespace graphical{
namespace object{

    class sprite_animation;

}// namespace object
}// namespace graphical
}// namespace interface
}// namespace cw

class cw::interface::graphical::object::sprite_animation{
public:

    sprite_animation(){
        current_frame = 0;
    }

    void set_origin(const glm::vec3& new_origin){
        for(auto& frame : frames){
            frame->set_origin(new_origin);
        }
    }

    void set_size(const glm::vec3& new_size){
        for(auto& frame : frames){
            frame->set_size(new_size);
        }
    }

    float duration;
    unsigned int current_frame;
    std::vector<std::shared_ptr<detail::sprite> > frames;
    
};// class sprite_animation