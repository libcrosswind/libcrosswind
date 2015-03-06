#pragma once

#include <vector>
#include <GL/glew.h>

namespace cw{
namespace simulation{
namespace gl{

	class vbo;

}// namespace gl
}// namespace simulation
}// namespace cw

class cw::simulation::gl::vbo{
public:
	vbo(unsigned short num_buffers = 1): id(0), allocated_buffers(num_buffers){
		glGenBuffers(allocated_buffers, &id);
	}

	~vbo(){
		glDeleteBuffers(allocated_buffers, &id);
	}

	void upload_vertex_array(const std::vector<float>& vertex_array){
		glBindBuffer(GL_ARRAY_BUFFER, id);

		glBufferData(GL_ARRAY_BUFFER, vertex_array.size()*sizeof(float), vertex_array.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void draw_vertex_array(const std::vector<float>& vertex_array){
		glBindBuffer(GL_ARRAY_BUFFER, id);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, vertex_array.size()/3);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
private:
	uint32_t id;
	unsigned short allocated_buffers;
};// class vbo