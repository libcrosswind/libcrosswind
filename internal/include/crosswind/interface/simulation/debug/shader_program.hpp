#pragma once

#include <string>
#include <cstdint>

namespace cw{
namespace interface{
namespace simulation{
namespace debug{

	class shader_program;

}// namespace debug
}// namespace simulation
}// namespace interface
}// namespace cw

class cw::interface::simulation::debug::shader_program{
public:
    shader_program(): 
    attributes_number(0), 
    program_id(0), 
    vertex_shader_id(0), 
    fragment_shader_id(0){

    }

    virtual ~shader_program(){

    }

    virtual void compile(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath) = 0;

    virtual void link() = 0;

    virtual void add_attribute(const std::string& attribute_name) = 0;

	virtual int32_t get_uniform_location(const std::string& uniform_name)  = 0;

    virtual void use() = 0;

    virtual void unuse() = 0;

protected:
	virtual void compile(const std::string& shader_filepath, const uint32_t& shader_id) = 0;

    uint32_t attributes_number;

    uint32_t program_id;

    uint32_t vertex_shader_id;
    uint32_t fragment_shader_id;

};// class shader_program