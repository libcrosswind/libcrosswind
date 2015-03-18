#pragma once

#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <crosswind/geometry/detail/vertex.hpp>
#include <crosswind/simulation/sprite.hpp>
#include <crosswind/simulation/detail/graphical_actor.hpp>

namespace cw{
namespace simulation{
namespace gl{

	class gl_sprite_batch;

	class gl_render_batch {
	public:
	    gl_render_batch(uint32_t v_offset, uint32_t v_count, uint32_t t_id) : 
	    vertex_offset(v_offset), 
	    vertex_count(v_count), 
	    texture_id(t_id) {

	    }

	    uint32_t vertex_offset;
	    uint32_t vertex_count;
	    uint32_t texture_id;
	};

}// namespace gl
}// namespace simulation
}// namespace cw

class cw::simulation::gl::gl_sprite_batch: public cw::simulation::detail::graphical_actor{
public:
	gl_sprite_batch(): vao_id(0), vbo_id(0){
		create_vertex_array();
	}

	void begin(){
	    batch_list.clear();
	    sprite_list.clear();
	}

	void upload(std::shared_ptr<sprite> sprite){
		sprite_list.push_back(sprite);
	}

	void end(){
    	std::stable_sort(sprite_list.begin(), sprite_list.end(), [](auto a, auto b){
		    return (a->texture_id < b->texture_id);
    	});
    	create_batch_list();
	}

	virtual void draw(){

	    glBindVertexArray(vao_id);

	    for (auto& batch : batch_list) {
	        glBindTexture(GL_TEXTURE_2D, batch->texture_id);
	        glDrawArrays(GL_TRIANGLES, batch->vertex_offset, batch->vertex_count);
	    }

	    glBindVertexArray(0);
	}

private:
	void create_vertex_array(){
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
                              sizeof(geometry::detail::vertex),
                              (void*)offsetof(geometry::detail::vertex, geometry::detail::vertex::position));

        glVertexAttribPointer(1,
                              4,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(geometry::detail::vertex),
                              (void*)offsetof(geometry::detail::vertex, geometry::detail::vertex::color));

        glVertexAttribPointer(2,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(geometry::detail::vertex),
                              (void*)offsetof(geometry::detail::vertex, geometry::detail::vertex::uv));

/*        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
*/
        glBindVertexArray(0);
	}

	void create_batch_list(){

	    std::vector <geometry::detail::vertex> vertices;

	    if (sprite_list.empty()) {
	        return; // Should throw exception.
	    }

    	uint32_t current_texture_id = 0;
    	uint32_t offset = 0;
	    for(auto& sprite : sprite_list){


	    	if(sprite->texture_id != current_texture_id){
	    		current_texture_id = sprite->texture_id;

	    		auto batch = 
	    		std::make_shared<gl_render_batch>(offset, 
    											  sprite->vertices.size(), 
    											  current_texture_id);
	    		
	    		batch_list.emplace_back(batch);

	    	} else {
                batch_list.back()->vertex_count += sprite->vertices.size();
	    	}

	    	vertices.insert(vertices.end(), sprite->vertices.begin(), sprite->vertices.end());

    		offset += sprite->vertices.size();

	    }

	    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	   
	    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(geometry::detail::vertex), nullptr, GL_DYNAMIC_DRAW);
	    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(geometry::detail::vertex), vertices.data());
	   
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:
	uint32_t vao_id;
	uint32_t vbo_id;

	std::vector<std::shared_ptr<gl_render_batch> > batch_list;
	std::vector<std::shared_ptr<sprite> > 	sprite_list;
};