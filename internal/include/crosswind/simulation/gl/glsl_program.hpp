#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <GL/glew.h>

#include <crosswind/platform/sdl/sdl_exception.hpp>

namespace cw{
namespace simulation{
namespace gl{

	class glsl_program;

}// namespace gl
}// namespace simulation
}// namespace cw

class cw::simulation::gl::glsl_program{
public:
    glsl_program(): 
    attributes_number(0), 
    program_id(0), 
    vertex_shader_id(0), 
    fragment_shader_id(0){

    }

    ~glsl_program(){

    }

    void compile(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath){
		program_id = glCreateProgram();

	    if ((vertex_shader_id = glCreateShader(GL_VERTEX_SHADER)) == 0) {
	            throw platform::sdl::sdl_exception("Could not create vertex shader");
	    }

	    if ((fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER)) == 0) {
	            throw platform::sdl::sdl_exception("Could not create fragment shader");
	    }	    

    	//Compile shaders
	    compile(vertex_shader_filepath, vertex_shader_id);
	    compile(fragment_shader_filepath, fragment_shader_id);
    }

    void link(){

	    glAttachShader(program_id, vertex_shader_id);
	    glAttachShader(program_id, fragment_shader_id);

	    glLinkProgram(program_id);

	    GLint status = 0;
	    glGetProgramiv(program_id, GL_LINK_STATUS, (int *)&status);

	    if (status == GL_FALSE){

	        GLint log_length = 0;
	        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

	        std::vector<char> error_log(log_length);
	        glGetProgramInfoLog(program_id, log_length, &log_length, &error_log[0]);

	        glDeleteProgram(program_id);
	        glDeleteShader(vertex_shader_id);
	        glDeleteShader(fragment_shader_id);

	        std::printf("%s\n", &(error_log[0]));
            throw platform::sdl::sdl_exception("Faled to link shaders");
	    }

	    glDetachShader(program_id, vertex_shader_id);
	    glDetachShader(program_id, fragment_shader_id);
	    glDeleteShader(vertex_shader_id);
	    glDeleteShader(fragment_shader_id);
    }

    void add_attribute(const std::string& attribute_name){
	    glBindAttribLocation(program_id, attributes_number++, attribute_name.c_str());
    }

    void use(){
    	glUseProgram(program_id);
    	//enable the attributes added with add_attribute
	    for (int i = 0; i < attributes_number; i++) {
	        glEnableVertexAttribArray(i);
	    }
    }

    void unuse(){
	    glUseProgram(0);
    	//disable the attributes added with add_attribute
	    for (int i = 0; i < attributes_number; i++) {
	        glDisableVertexAttribArray(i);
	    }
    }

private:
	void compile(const std::string& shader_filepath, const uint32_t& shader_id){

	    //Open the file
	    std::ifstream shader_file(shader_filepath);
	    if (shader_file.fail()) {
	        perror(shader_filepath.c_str());
	       	throw platform::sdl::sdl_exception("Failed to open " + shader_filepath);
	    }

	    std::string file_contents = "";
	    std::string line;

	    while (std::getline(shader_file, line)) {
	        file_contents += line + "\n";
	    }

	    shader_file.close();

	    const char* contents_ptr = file_contents.c_str();
	    glShaderSource(shader_id, 1, &contents_ptr, nullptr);

	    glCompileShader(shader_id);

	    GLint status = 0;

	    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);

	    if (status == GL_FALSE){

	        GLint log_legth = 0;
	        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_legth);

	        std::vector<char> error_log(log_legth);
	        glGetShaderInfoLog(shader_id, log_legth, &log_legth, &error_log[0]);

	        glDeleteShader(shader_id); 
	        std::printf("%s\n", &(error_log[0]));
            throw platform::sdl::sdl_exception("Faled to compile shader: " + shader_filepath);
	    }
	}


    int attributes_number;

    uint32_t program_id;

    uint32_t vertex_shader_id;
    uint32_t fragment_shader_id;
    
};// class glsl_program