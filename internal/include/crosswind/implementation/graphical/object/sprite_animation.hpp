#pragma once

#include <memory>
#include <vector>

#include <crosswind/interface/graphical/object/sprite_animation.hpp>

namespace cw{
namespace implementation{
namespace graphical{
namespace object{

    class sprite_animation;

}// namespace object
}// namespace graphical
}// namespace implementation
}// namespace cw

class cw::implementation::graphical::object::sprite_animation: public cw::interface::graphical::object::sprite_animation{
public:
    sprite_animation(){

    }

    virtual void flip(bool default_x){

        if(x_orientation){
            if(!default_x){
                for(int i = 0; i<frames.size(); i++){
                    frames[i]->flip();
                }

                x_orientation = default_x;
            }

        } else {

            if(default_x){
                for(int i = 0; i<frames.size(); i++){
                    frames[i]->flip();
                }

                x_orientation = default_x;
            }
        }
    }

};// class sprite_animation