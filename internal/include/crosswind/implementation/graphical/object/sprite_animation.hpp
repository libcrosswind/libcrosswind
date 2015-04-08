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

    virtual ~sprite_animation(){

    }

};// class sprite_animation