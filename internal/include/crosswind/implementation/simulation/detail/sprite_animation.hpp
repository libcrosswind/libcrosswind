#pragma once

#include <memory>
#include <vector>
#include <string>
#include <crosswind/simulation/sprite.hpp>

namespace cw{
namespace simulation{

class sprite_animation;

}// namespace simulation	
}// namespace cw

class cw::simulation::sprite_animation{
public:

    sprite_animation(){
        current_frame = 0;
        x_orientation = true;
    }

    void flip(bool default_x){

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

    bool x_orientation;

    double duration;
    unsigned int current_frame;
    std::vector<std::shared_ptr<sprite> > frames;
};// class sprite_animation