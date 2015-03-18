#pragma once

#include <glm/glm.hpp>

#include <crosswind/geometry/rectangle.hpp>
//#include <crosswind/simulation/detail/standard_actor.hpp>
//#include <crosswind/simulation/detail/graphical_actor.hpp>
//#include <crosswind/simulation/gl/gl_vbo.hpp>

namespace cw{
namespace simulation{

	class sprite;

}// namespace simulation
}// namespace cw


/* previous inheritance schema
public cw::simulation::detail::standard_actor,
public cw::simulation::gl::gl_vbo*/

class cw::simulation::sprite: public cw::geometry::rectangle {
public:
	sprite(const glm::vec3& p, 
           const glm::vec3& s, 
           const glm::vec4& uv, 
           const uint32_t& t_id):
            cw::geometry::rectangle(p, s),
            texture_id(t_id){

        // first triangle
        vertices[0].set_uv(uv.z, uv.w); // top right
        vertices[1].set_uv(uv.x, uv.w); // top left
        vertices[2].set_uv(uv.x, uv.y); // bottom left

        // second triangle
        vertices[3].set_uv(uv.x, uv.y); // bottom left
        vertices[4].set_uv(uv.z, uv.y); // bottom right
        vertices[5].set_uv(uv.z, uv.w); // top right

	}

    uint32_t texture_id;
};// class sprite