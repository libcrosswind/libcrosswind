#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"

// forward declarations
namespace cw{
namespace graphical{
namespace object{

    class sprite;

}// namespace object
}// namespace graphical
}// namespace cw

namespace cw{
namespace graphical{
namespace object{

class sprite_animation{
public:
    sprite_animation();

    ~sprite_animation();

    void set_origin(const glm::vec3& new_origin);

    void set_size(const glm::vec3& new_size);

    void flip(bool default_x);

    bool x_orientation;

    float duration;
    unsigned int current_frame;
    std::vector<std::shared_ptr<sprite> > frames;

};// class sprite_animation
 
}// namespace object
}// namespace graphical
}// namespace cw