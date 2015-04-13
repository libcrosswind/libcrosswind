#pragma once

#include <cstdint>

namespace cw{
namespace graphical{
namespace opengl{

class render_batch{
public:
    render_batch(uint32_t v_offset, uint32_t v_count, uint32_t t_id);

    ~render_batch();

    uint32_t vertex_offset;
    uint32_t vertex_count;
    uint32_t texture_id;

};

}// namespace opengl
}// namespace graphical
}// namespace implementation
}// namespace cw
