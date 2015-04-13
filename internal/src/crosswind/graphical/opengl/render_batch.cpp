#include "crosswind/graphical/opengl/render_batch.hpp"

cw::graphical::opengl::render_batch::render_batch(uint32_t v_offset, uint32_t v_count, uint32_t t_id) : 
vertex_offset(v_offset), 
vertex_count(v_count), 
texture_id(t_id){

}

cw::graphical::opengl::render_batch::~render_batch(){

}