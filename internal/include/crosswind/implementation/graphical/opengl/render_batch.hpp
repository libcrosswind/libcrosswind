#pragma once

#include <cstdint>
#include <crosswind/interface/graphical/detail/render_batch.hpp>


namespace cw{
namespace implementation{
namespace graphical{
namespace opengl{

	class render_batch;

}// namespace opengl
}// namespace graphical
}// namespace implementation
}// namespace cw

class cw::implementation::graphical::opengl::render_batch: public cw::interface::graphical::detail::render_batch {
public:
    render_batch(uint32_t v_offset, uint32_t v_count, uint32_t t_id) : 
    cw::interface::graphical::detail::render_batch(v_offset, v_count, t_id){

    }

    virtual ~render_batch(){

    }
};