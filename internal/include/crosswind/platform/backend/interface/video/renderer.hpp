#pragma once

#include <crosswind/simulation/model.hpp>
#include <crosswind/simulation/gl/gl_sprite_batch.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace interface{
namespace video{

	class renderer;

}// namespace video
}// namespace interface
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::interface::video::renderer{
public:
	renderer(){

        sprite_batch = std::make_shared<cw::simulation::gl::gl_sprite_batch>();
        
        glsl_program = std::make_shared<cw::simulation::gl::glsl_program>();
        std::string vertex_shader   = "assets/default/graphics/shaders/texture_shading.vert";
        std::string fragment_shader = "assets/default/graphics/shaders/texture_shading.frag";
        
        glsl_program->compile(vertex_shader, fragment_shader);
        glsl_program->add_attribute("vertex_position");
        glsl_program->add_attribute("vertex_color");
        glsl_program->add_attribute("vertex_uv");
        glsl_program->link();
        
	}



	void begin(){
        glsl_program->use();

        glActiveTexture(GL_TEXTURE0); //Need to integrate this into batch list or program keymap

        auto texture_location = glsl_program->get_uniform_location("texture_sampler");
        glUniform1i(texture_location, 0);

        sprite_batch->begin();

	}

	void set_uniform_matrix(const std::string& uniform_matrix_name, auto value){

        auto uniform_matrix_location = glsl_program->get_uniform_location(uniform_matrix_name);
        glUniformMatrix4fv(uniform_matrix_location, 1, GL_FALSE, glm::value_ptr(value));

	}

	void upload(std::shared_ptr<cw::simulation::model> model){
		sprite_batch->upload(model);
	}

	void end(){
        sprite_batch->end();
		glsl_program->unuse();
	}



private:
    std::shared_ptr<cw::simulation::gl::glsl_program>    glsl_program;
    std::shared_ptr<cw::simulation::gl::gl_sprite_batch> sprite_batch;
};