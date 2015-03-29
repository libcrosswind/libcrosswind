#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <GL/glew.h>

#include <crosswind/interface/simulation/debug/shader_program.hpp>
#include <crosswind/implementation/platform/exception.hpp>

namespace cw{
namespace implementation{
namespace simulation{
namespace debug{
namespace opengl{

    class shader_program;

}// namespace debug
}// namespace opengl
}// namespace simulation
}// namespace implementation
}// namespace cw

class cw::implementation::simulation::debug::opengl::shader_program: public cw::interface::simulation::debug::shader_program{
public:
    shader_program(){

    }

    virtual ~shader_program(){

    }

    virtual void compile(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath){
        program_id = glCreateProgram();

        if ((vertex_shader_id = glCreateShader(GL_VERTEX_SHADER)) == 0) {
                throw platform::exception("Could not create vertex shader");
        }

        if ((fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER)) == 0) {
                throw platform::exception("Could not create fragment shader");
        }       

        //Compile shaders
        compile(vertex_shader_filepath, vertex_shader_id);
        compile(fragment_shader_filepath, fragment_shader_id);
    }

    virtual void link(){

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
            throw platform::exception("Faled to link shaders");
        }

        glDetachShader(program_id, vertex_shader_id);
        glDetachShader(program_id, fragment_shader_id);
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
    }

    virtual void add_attribute(const std::string& attribute_name){
        glBindAttribLocation(program_id, attributes_number++, attribute_name.c_str());
    }

    virtual int32_t get_uniform_location(const std::string& uniform_name) {
        auto location = glGetUniformLocation(program_id, uniform_name.c_str());
        if (location == GL_INVALID_INDEX) {
            throw platform::exception("Uniform " + uniform_name + " not found in shader");
        }
        return location;
    }

    virtual void use(){
        glUseProgram(program_id);
        //enable the attributes added with add_attribute
        for (int i = 0; i < attributes_number; i++) {
            glEnableVertexAttribArray(i);
        }
    }

    virtual void unuse(){
        glUseProgram(0);
        //disable the attributes added with add_attribute
        for (int i = 0; i < attributes_number; i++) {
            glDisableVertexAttribArray(i);
        }
    }

protected:
    virtual void compile(const std::string& shader_filepath, const uint32_t& shader_id){

        //Open the file
        std::ifstream shader_file(shader_filepath);
        if (shader_file.fail()) {
            perror(shader_filepath.c_str());
            throw platform::exception("Failed to open " + shader_filepath);
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
            throw platform::exception("Faled to compile shader: " + shader_filepath);
        }
    }


};// class shader_program