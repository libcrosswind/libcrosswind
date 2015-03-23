#pragma once

#include <cstdint>

namespace cw{
namespace interface{
namespace graphical{
namespace detail{

	class render_batch;

}// namespace opengl
}// namespace graphical
}// namespace interface
}// namespace cw

class cw::interface::graphical::opengl::render_batch {
public:
    render_batch(uint32_t v_offset, uint32_t v_count, uint32_t t_id) : 
    vertex_offset(v_offset), 
    vertex_count(v_count), 
    texture_id(t_id) {

    }

    uint32_t vertex_offset;
    uint32_t vertex_count;
    uint32_t texture_id;
};