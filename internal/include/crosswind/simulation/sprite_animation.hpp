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

class cw::simulation::detail::sprite_animation{
public:
    sprite_animation(){
        current_frame = 0;
    }

    double duration;
    unsigned int current_frame;
    std::vector<std::shared_ptr<sprite> > frames;
};// class sprite_animation