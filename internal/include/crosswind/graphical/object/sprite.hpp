#pragma once

#include "glm/glm.hpp"

#include "crosswind/graphical/object/mesh.hpp"

namespace cw{
namespace graphical{
namespace object{

class sprite: public mesh {
public:
	sprite(const glm::vec3& c_origin,
           const glm::vec3& c_size,
           const glm::vec4& c_color  = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
           const glm::vec4& c_uv     = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
           const uint32_t&  c_id = 0);

    virtual void set_origin(const glm::vec3& new_origin) override;

    virtual void set_size(const glm::vec3& new_size) override;

    glm::vec4 get_color();
    glm::vec4 get_uv();

    void h_flip();
    void v_flip();

    bool get_h_flip();
    bool get_v_flip();

    uint32_t texture_id;

private:
    bool xFlipped;
    bool vFlipped;

    glm::vec4 color;
    glm::vec4 uv;
    
};// class sprite

}// namespace object
}// namespace graphical
}// namespace cw