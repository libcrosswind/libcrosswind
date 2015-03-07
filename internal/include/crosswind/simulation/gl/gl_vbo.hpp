#pragma once

#include <cstddef>
#include <vector>
#include <GL/glew.h>

#include <crosswind/geometry/detail/vertex.hpp>

namespace cw{
namespace simulation{
namespace gl{

	class gl_vbo;

}// namespace gl
}// namespace simulation
}// namespace cw

class cw::simulation::gl::gl_vbo{
public:
	gl_vbo(unsigned short num_buffers = 1): id(0), allocated_buffers(num_buffers){
		glGenBuffers(allocated_buffers, &id);
	}

	~gl_vbo(){
		glDeleteBuffers(allocated_buffers, &id);
	}

	void upload_vertex_array(const std::vector<geometry::detail::vertex>& vertex_array){
		glBindBuffer(GL_ARRAY_BUFFER, id);

		glBufferData(GL_ARRAY_BUFFER,
                     sizeof(geometry::detail::vertex)*vertex_array.size(),
                     vertex_array.data(),
                     GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void draw_vertex_array(const std::vector<geometry::detail::vertex>& vertex_array){
		glBindBuffer(GL_ARRAY_BUFFER, id);

		glEnableVertexAttribArray(0);

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

		glDrawArrays(GL_TRIANGLES, 0, vertex_array.size());

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
private:
	uint32_t id;
	unsigned short allocated_buffers;
};// class gl_vbo