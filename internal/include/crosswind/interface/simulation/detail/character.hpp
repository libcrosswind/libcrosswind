#pragma once

#include <glm/glm.hpp>

namespace cw{
namespace interface{
namespace simulation{
namespace detail{

	class character;

}// namespace detail
}// namespace simulation
}// namespace interface
}// namespace cw

class cw::interface::simulation::detail::character{
public:
    character(const glm::vec3& c_origin,
              const glm::vec2& c_size,
              const glm::vec3& c_scale,
              const glm::vec3& c_unit_value,
              const float&     c_step_height): 
    origin(c_origin), 
    size(c_size), 
    scale(c_scale), 
    unit_value(c_unit_value), 
    step_height(c_step_height),
    speed(0.0f, 0.0f, 0.0f){

    }

    virtual void set_origin(const glm::vec3& origin) = 0;
    virtual glm::vec3 get_origin() = 0;


    virtual void set_jump_speed(const float& spd) = 0;

    virtual void jump() = 0;

    virtual void set_speed(const glm::vec3& spd) = 0;
    virtual glm::vec3 get_speed() = 0;

    virtual bool on_ground() = 0;

    virtual void* get_character_object() = 0;

protected:
    glm::vec3 origin;
    glm::vec2 size;
    glm::vec3 scale;
    glm::vec3 unit_value;

    float step_height;

    glm::vec3 speed;

};// class character