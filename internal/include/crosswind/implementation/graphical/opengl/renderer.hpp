#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <crosswind/interface/graphical/detail/renderer.hpp>
#include <crosswind/implementation/graphical/opengl/sprite_batch.hpp>
#include <crosswind/implementation/graphical/opengl/shader_program.hpp>

namespace cw{
namespace implementation{
namespace graphical{
namespace opengl{

	class renderer;

}// namespace opengl
}// namespace graphical
}// namespace implementation
}// namespace cw

class cw::implementation::graphical::opengl::renderer: public cw::interface::graphical::detail::renderer{
public:
	renderer(){

        sprite_batch                = std::make_shared<class sprite_batch>();        
        shader_program              = std::make_shared<class shader_program>();

        std::string vertex_shader   = "assets/default/graphics/shaders/texture_shading.vert";
        std::string fragment_shader = "assets/default/graphics/shaders/texture_shading.frag";

        shader_program->compile(vertex_shader, fragment_shader);
        shader_program->add_attribute("vertex_position");
        shader_program->add_attribute("vertex_color");
        shader_program->add_attribute("vertex_uv");
        shader_program->link();
        
	}

	void begin(){

        shader_program->use();

        glActiveTexture(GL_TEXTURE0); //Need to integrate this into batch list or program keymap

        auto texture_location = shader_program->get_uniform_location("texture_sampler");
        glUniform1i(texture_location, 0);

        sprite_batch->clear();

	}

	void set_uniform_matrix(const std::string& uniform_matrix_name, const glm::mat4& value){

        auto uniform_matrix_location = shader_program->get_uniform_location(uniform_matrix_name);
        glUniformMatrix4fv(uniform_matrix_location, 1, GL_FALSE, glm::value_ptr(value));

	}


/*	void upload(std::shared_ptr<cw::simulation::model> model){
		batch->upload(model);
	}*/

    void draw(){

        sprite_batch->create();
        sprite_batch->draw();

    }

	void end(){

		shader_program->unuse();
        
	}

private:
    std::shared_ptr<shader_program> shader_program;
    std::shared_ptr<sprite_batch>   sprite_batch;
};