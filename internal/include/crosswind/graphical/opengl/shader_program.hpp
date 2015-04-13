#pragma once

#include <string>
#include <cstdint>

namespace cw{
namespace graphical{
namespace opengl{
 
class shader_program{
public:
    shader_program();

    ~shader_program();

    void compile(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);

    void link();

    void add_attribute(const std::string& attribute_name);

	int32_t get_uniform_location(const std::string& uniform_name);

    void use();

    void unuse();

private:
	void compile(const std::string& shader_filepath, const uint32_t& shader_id);

    int attributes_number;
    uint32_t program_id;
    uint32_t vertex_shader_id;
    uint32_t fragment_shader_id;

};// class shader_program

}// namespace opengl
}// namespace graphical
}// namespace cw