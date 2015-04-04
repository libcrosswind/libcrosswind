#pragma once

#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <crosswind/interface/graphical/detail/vertex.hpp>
#include <crosswind/interface/graphical/detail/sprite.hpp>
#include <crosswind/interface/graphical/detail/sprite_batch.hpp>
#include <crosswind/implementation/graphical/opengl/render_batch.hpp>

namespace cw{
namespace implementation{
namespace graphical{
namespace opengl{

	class sprite_batch;

}// namespace opengl
}// namespace graphical
}// namespace implementation
}// namespace cw

class cw::implementation::graphical::opengl::sprite_batch: public cw::interface::graphical::detail::sprite_batch{
public:
	sprite_batch(): vao_id(0), vbo_id(0){
		create_vertex_array();
	}

	void clear(){
	    batch_list.clear();
	    sprite_list.clear();
	}

	void upload(const std::map<std::string, std::shared_ptr<interface::graphical::detail::sprite> >& render_list){

		for(auto& sprite: render_list){
			sprite_list.push_back(sprite.second);
		}

	}

	void create(){
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
                              sizeof(interface::graphical::detail::vertex),
                              (void*)offsetof(interface::graphical::detail::vertex,
		                                      interface::graphical::detail::vertex::position));

        glVertexAttribPointer(1,
                              4,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(interface::graphical::detail::vertex),
                              (void*)offsetof(interface::graphical::detail::vertex,
		                                      interface::graphical::detail::vertex::color));

        glVertexAttribPointer(2,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(interface::graphical::detail::vertex),
                              (void*)offsetof(interface::graphical::detail::vertex,
		                                      interface::graphical::detail::vertex::uv));

        glBindVertexArray(0);
	}

	void create_batch_list(){

	    std::vector <interface::graphical::detail::vertex> vertices;

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
	   
	    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(interface::graphical::detail::vertex), nullptr, GL_DYNAMIC_DRAW);
	    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(interface::graphical::detail::vertex), vertices.data());
	   
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:
	uint32_t vao_id;
	uint32_t vbo_id;
};