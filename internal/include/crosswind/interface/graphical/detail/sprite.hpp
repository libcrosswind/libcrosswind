#pragma once

#include <glm/glm.hpp>

#include <crosswind/interface/graphical/detail/mesh.hpp>

namespace cw{
namespace interface{
namespace graphical{
namespace detail{

	class sprite;

}// namespace detail
}// namespace graphical
}// namespace interface
}// namespace cw

class cw::interface::graphical::detail::sprite: public cw::interface::graphical::detail::mesh {
public:
	sprite(const glm::vec3& c_origin,
           const glm::vec3& s,
           const glm::vec4& c  = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
           const glm::vec4& uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
           const uint32_t& t_id = 0): cw::interface::graphical::detail::mesh(c_origin, s),
            texture_id(t_id){

            auto px = c_origin.x - s.x/2.0f;
            auto py = c_origin.y - s.y/2.0f;
            auto pz = c_origin.z - s.z/2.0f;
            auto pw = 1.0f;

            auto dx = s.x;
            auto dy = s.y;
            auto dz = s.z;

            detail::vertex top_right(glm::vec4(px + dx, py + dy, pz, pw), c, glm::vec2(0.0f, 0.0f));
            detail::vertex top_left(glm::vec4(px, py + dy, pz, pw), c, glm::vec2(0.0f));
            detail::vertex bottom_right(glm::vec4(px + dx, py, pz, pw), c, glm::vec2(0.0f));
            detail::vertex bottom_left(glm::vec4(px, py, pz, pw), c, glm::vec2(0.0f));

            vertices = {
                // First triangle
                top_right,
                top_left,
                bottom_left,
                //Second triangle
                bottom_left,
                bottom_right,
                top_right
            };

            // first triangle
            vertices[0].set_uv(uv.z, uv.w); // top right
            vertices[1].set_uv(uv.x, uv.w); // top left
            vertices[2].set_uv(uv.x, uv.y); // bottom left

            // second triangle
            vertices[3].set_uv(uv.x, uv.y); // bottom left
            vertices[4].set_uv(uv.z, uv.y); // bottom right
            vertices[5].set_uv(uv.z, uv.w); // top right

            set_origin(origin);
	}

    virtual void set_origin(const glm::vec3& new_origin) override {
        origin = new_origin;

        auto px = new_origin.x - size.x/2.0f;
        auto py = new_origin.y - size.y/2.0f;
        auto pz = new_origin.z - size.z/2.0f;
        auto pw = 1.0f;

        auto dx = size.x;
        auto dy = size.y;
        auto dz = size.z;

        glm::vec4 top_right (px + dx, py + dy, pz, pw);
        glm::vec4 top_left(px, py + dy, pz, pw);
        glm::vec4 bottom_right(px + dx, py, pz, pw);
        glm::vec4 bottom_left(px, py, pz, pw);

        vertices[0].set_position(top_right);
        vertices[1].set_position(top_left);
        vertices[2].set_position(bottom_left);

        vertices[3].set_position(bottom_left);
        vertices[4].set_position(bottom_right);
        vertices[5].set_position(top_right);


    }

    virtual void set_size(const glm::vec3& new_size) override {

        size = new_size;

        set_origin(get_origin());

    }


    void flip(){

        auto tr = vertices[0];  // top right
        auto tl = vertices[1];  // top left

        vertices[0] = tl;       // flip
        vertices[1] = tr;       // flip
        vertices[5] = tl;       // flip

        auto br = vertices[4];  // bottom right
        auto bl = vertices[3];  // bottom left

        vertices[2] = br;       // flip
        vertices[3] = br;       // flip
        vertices[4] = bl;       // flip
    }

    uint32_t texture_id;
    
};// class sprite