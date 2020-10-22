#include "GL/glew.h"
#include "glm/gtc/type_ptr.hpp"

#include "crosswind/graphical/opengl/renderer.hpp"
#include "crosswind/graphical/opengl/sprite_batch.hpp"
#include "crosswind/graphical/opengl/shader_program.hpp"

cw::graphical::opengl::renderer::renderer(){

    sprite_batch                = std::make_shared<class sprite_batch>();        
    shader_program              = std::make_shared<class shader_program>();

    std::string vertex_shader   = "resources/assets/engine/graphics/shaders/texture_shading.vert";
    std::string fragment_shader = "resources/assets/engine/graphics/shaders/texture_shading.frag";

    shader_program->compile(vertex_shader, fragment_shader);
    shader_program->add_attribute("vertex_position");
    shader_program->add_attribute("vertex_color");
    shader_program->add_attribute("vertex_uv");
    shader_program->link();
    
}

void cw::graphical::opengl::renderer::begin(){

    shader_program->use();

    glActiveTexture(GL_TEXTURE0); //Need to integrate this into batch list or program keymap

    auto texture_location = shader_program->get_uniform_location("texture_sampler");
    glUniform1i(texture_location, 0);

    sprite_batch->clear();

}

void cw::graphical::opengl::renderer::set_uniform_matrix(const std::string& uniform_matrix_name, const glm::mat4& value){

    auto uniform_matrix_location = shader_program->get_uniform_location(uniform_matrix_name);
    glUniformMatrix4fv(uniform_matrix_location, 1, GL_FALSE, glm::value_ptr(value));

}

void cw::graphical::opengl::renderer::upload(std::shared_ptr<object::sprite> render_sprite){

    sprite_batch->upload(render_sprite);

}

void cw::graphical::opengl::renderer::draw(){

    sprite_batch->create();
    sprite_batch->draw();

}

void cw::graphical::opengl::renderer::end(){

	shader_program->unuse();
    
}
 