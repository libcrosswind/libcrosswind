#include <algorithm>

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "crosswind/graphical/opengl/sprite_batch.hpp"
#include "crosswind/graphical/opengl/render_batch.hpp"
#include "crosswind/graphical/object/sprite.hpp"
#include "crosswind/graphical/object/vertex.hpp"

cw::graphical::opengl::sprite_batch::sprite_batch(): 
vao_id(0), vbo_id(0){

		create_vertex_array();

}

void cw::graphical::opengl::sprite_batch::clear(){

    batch_list.clear();
    sprite_list.clear();

}

void cw::graphical::opengl::sprite_batch::upload(std::shared_ptr<object::sprite> render_sprite){
		
		sprite_list.push_back(render_sprite);

}

void cw::graphical::opengl::sprite_batch::create(){

	std::stable_sort(sprite_list.begin(), sprite_list.end(), [](auto a, auto b){
	    return (a->texture_id < b->texture_id);
	});
	create_batch_list();

}

void cw::graphical::opengl::sprite_batch::draw(){

    glBindVertexArray(vao_id);

    for (auto& batch : batch_list) {
        glBindTexture(GL_TEXTURE_2D, batch->texture_id);
        glDrawArrays(GL_TRIANGLES, batch->vertex_offset, batch->vertex_count);
    }

    glBindVertexArray(0);

}

void cw::graphical::opengl::sprite_batch::create_vertex_array(){

	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	glGenBuffers(1, &vbo_id);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0,
                          4,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(object::vertex),
                          (void*)offsetof(object::vertex,
	                                      object::vertex::position));

    glVertexAttribPointer(1,
                          4,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(object::vertex),
                          (void*)offsetof(object::vertex,
	                                      object::vertex::color));

    glVertexAttribPointer(2,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(object::vertex),
                          (void*)offsetof(object::vertex,
	                                      object::vertex::uv));

    glBindVertexArray(0);

}

void cw::graphical::opengl::sprite_batch::create_batch_list(){

    std::vector <object::vertex> vertices;

    if (sprite_list.empty()) {
        return; // Should throw exception.
    }

	uint32_t current_texture_id = 0;
	uint32_t offset = 0;
    for(auto& sprite : sprite_list){

		auto& sprite_vertices = sprite->get_vertices();

    	if(sprite->texture_id != current_texture_id){
    		current_texture_id = sprite->texture_id;

    		auto render_batch = 
    		std::make_shared<class render_batch>(offset,
		                                         sprite_vertices.size(),
											     current_texture_id);
    		
    		batch_list.emplace_back(render_batch);

    	} else {
            batch_list.back()->vertex_count += sprite_vertices.size();
    	}

    	vertices.insert(vertices.end(), sprite_vertices.begin(), sprite_vertices.end());

		offset += sprite_vertices.size();

    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
   
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(object::vertex), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(object::vertex), &vertices[0]);
   
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
 