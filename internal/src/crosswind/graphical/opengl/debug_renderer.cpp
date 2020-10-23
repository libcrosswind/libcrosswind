#include <vector>
#include "GL/glew.h"
#include "glm/gtc/type_ptr.hpp"

#include "crosswind/graphical/opengl/debug_renderer.hpp"

#include "crosswind/simulation/debug/opengl/simulation_shader_program.hpp"
#include "crosswind/simulation/debug/opengl/simulation_vertex.hpp"

cw::graphical::opengl::debug_renderer::debug_renderer() {

	debug_shader_program = std::make_shared<class cw::simulation::debug::opengl::simulation_shader_program>();
	std::string debug_vertex_shader = "resources/assets/engine/graphics/shaders/primitive_shading.vert";
	std::string debug_fragment_shader = "resources/assets/engine/graphics/shaders/primitive_shading.frag";

	debug_shader_program->compile(debug_vertex_shader, debug_fragment_shader);
	debug_shader_program->add_attribute("vertex_position");
	debug_shader_program->add_attribute("vertex_color");
	debug_shader_program->link();

	glGenBuffers(1, &debug_vbo_id);


}

cw::graphical::opengl::debug_renderer::~debug_renderer() {
	glDeleteBuffers(1, &debug_vbo_id);
}

void cw::graphical::opengl::debug_renderer::set_uniform_matrix(const glm::mat4& value) {

	perspective = value;
}

void cw::graphical::opengl::debug_renderer::draw_line(const glm::ivec3& f, const glm::ivec3& t, const glm::vec3& c) {

	debug_shader_program->use();

	auto projection_matrix_location = debug_shader_program->get_uniform_location("projection_matrix");

	glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(perspective));

	glm::vec4 n_from(f.x, f.y, f.z, 1.0);
	glm::vec4 n_to(t.x, t.y, t.z, 1.0);
	glm::vec4 color(c.r, c.g, c.b, 1.0);
	glm::vec2 u(0.0, 0.0);

	std::vector<cw::simulation::debug::opengl::simulation_vertex> vertex_array;
	cw::simulation::debug::opengl::simulation_vertex a(n_from, color, u);
	cw::simulation::debug::opengl::simulation_vertex b(n_to, color, u);
	vertex_array.push_back(a);
	vertex_array.push_back(b);

	//upload_vertex_array(vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, debug_vbo_id);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(cw::simulation::debug::opengl::simulation_vertex) * vertex_array.size(),
		vertex_array.data(),
		GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindBuffer(GL_ARRAY_BUFFER, debug_vbo_id);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(cw::simulation::debug::opengl::simulation_vertex),
		(void*)offsetof(cw::simulation::debug::opengl::simulation_vertex, cw::simulation::debug::opengl::simulation_vertex::position));

	glVertexAttribPointer(1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(cw::simulation::debug::opengl::simulation_vertex),
		(void*)offsetof(cw::simulation::debug::opengl::simulation_vertex, cw::simulation::debug::opengl::simulation_vertex::color));

	glDrawArrays(GL_POINTS, 0, (int)vertex_array.size());
	glDrawArrays(GL_LINES, 0, (int)vertex_array.size());


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	debug_shader_program->unuse();
}

void cw::graphical::opengl::debug_renderer::enqueue(const glm::ivec3& f, const glm::ivec3& t, const glm::vec3& c) {
	render_queue.push_back({ f, t, c });
}

void cw::graphical::opengl::debug_renderer::flush() {
	for (auto line : render_queue) {
		draw_line(std::get<0>(line), std::get<1>(line), std::get<2>(line));
	}

	render_queue.clear();
}

void cw::graphical::opengl::debug_renderer::debug_draw(const glm::ivec4& r) {
	enqueue(glm::ivec3(r.x, r.y, 0), glm::ivec3(r.x + r.z, r.y, 0), glm::vec3(1.0, 0.0, 0.0));
	enqueue(glm::ivec3(r.x + r.z, r.y, 0), glm::ivec3(r.x + r.z, r.y + r.w, 0), glm::vec3(1.0, 0.0, 0.0));
	enqueue(glm::ivec3(r.x + r.z, r.y + r.w, 0), glm::ivec3(r.x, r.y + r.w, 0), glm::vec3(1.0, 0.0, 0.0));
	enqueue(glm::ivec3(r.x, r.y, 0), glm::ivec3(r.x, r.y + r.w, 0), glm::vec3(1.0, 0.0, 0.0));
}

