#include <iostream>

#include "GL/glew.h"
#include "glm/gtc/type_ptr.hpp"

#include "crosswind/simulation/debug/opengl/drawer.hpp"
#include "crosswind/simulation/debug/opengl/shader_program.hpp"

cw::simulation::debug::opengl::drawer::drawer():
debug_mode(btIDebugDraw::DBG_DrawWireframe){

		shader_program = std::make_shared<class shader_program>();
		std::string vertex_shader   = "assets/engine/graphics/shaders/primitive_shading.vert";
		std::string fragment_shader = "assets/engine/graphics/shaders/primitive_shading.frag";

		shader_program->compile(vertex_shader, fragment_shader);
		shader_program->add_attribute("vertex_position");
		shader_program->add_attribute("vertex_color");
		shader_program->link();

		glGenBuffers(1, &vbo_id);
}

cw::simulation::debug::opengl::drawer::~drawer(){
	glDeleteBuffers(1, &vbo_id);
}

void cw::simulation::debug::opengl::drawer::upload_vertex_array(const std::vector<vertex>& vertex_array){

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER,
	sizeof(vertex)*vertex_array.size(),
	vertex_array.data(),
	GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void cw::simulation::debug::opengl::drawer::update(const glm::mat4& f_perspective,
														           const glm::vec3& f_scale){

	perspective = f_perspective;
	scale 		= f_scale;

}


void cw::simulation::debug::opengl::drawer::drawLine(const btVector3& from,
																     const btVector3& to, 
																     const btVector3& fromColor, 
																     const btVector3& toColor){

}

void cw::simulation::debug::opengl::drawer::drawLine(const btVector3& f,
															         const btVector3& t, 
															         const btVector3& color){

	btVector3 from(f.getX() / scale.x, f.getY() / scale.y, f.getZ() / scale.z);
	btVector3 to(t.getX() / scale.x, t.getY() / scale.y, t.getZ() / scale.z);


	shader_program->use();

	auto projection_matrix_location = shader_program->get_uniform_location("projection_matrix");

	glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(perspective));

	glm::vec4 n_from(from.getX(), from.getY(), from.getZ(), 1.0);
	glm::vec4 n_to(to.getX(), to.getY(), to.getZ(),1.0);
	glm::vec4 c(color.getX(), color.getY(), color.getZ(), 1.0);
	glm::vec2 u(0.0, 0.0);

	std::vector<vertex> vertex_array;
	vertex a(n_from, c, u);
	vertex b(n_to, c, u);
	vertex_array.push_back(a);
	vertex_array.push_back(b);

	upload_vertex_array(vertex_array);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertex),
			(void*)offsetof(vertex, vertex::position));

	glVertexAttribPointer(1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertex),
			(void*)offsetof(vertex, vertex::color));

	glDrawArrays( GL_POINTS, 0, vertex_array.size() );
	glDrawArrays( GL_LINES, 0, vertex_array.size() );


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader_program->unuse();

}

void cw::simulation::debug::opengl::drawer::drawSphere(const btVector3& p,
													   btScalar radius,
													   const btVector3& color){

	glColor4f (color.getX(), color.getY(), color.getZ(), btScalar(1.0f));
	glPushMatrix ();
	glTranslatef (p.getX(), p.getY(), p.getZ());

	int lats = 5;
	int longs = 5;

	int i, j;
	for(i = 0; i <= lats; i++) {
		btScalar lat0 = SIMD_PI * (-btScalar(0.5) + (btScalar) (i - 1) / lats);
		btScalar z0  = radius*sin(lat0);
		btScalar zr0 =  radius*cos(lat0);

		btScalar lat1 = SIMD_PI * (-btScalar(0.5) + (btScalar) i / lats);
		btScalar z1 = radius*sin(lat1);
		btScalar zr1 = radius*cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs; j++) {
			btScalar lng = 2 * SIMD_PI * (btScalar) (j - 1) / longs;
			btScalar x = cos(lng);
			btScalar y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}

	glPopMatrix();

}

void cw::simulation::debug::opengl::drawer::drawTriangle(const btVector3& a,
														 const btVector3& b,
														 const btVector3& c,
														 const btVector3& color,
														 btScalar alpha){

	{
		const btVector3	n=btCross(b-a,c-a).normalized();
		glBegin(GL_TRIANGLES);
		glColor4f(color.getX(), color.getY(), color.getZ(),alpha);
		glNormal3d(n.getX(),n.getY(),n.getZ());
		glVertex3d(a.getX(),a.getY(),a.getZ());
		glVertex3d(b.getX(),b.getY(),b.getZ());
		glVertex3d(c.getX(),c.getY(),c.getZ());
		glEnd();
	}

}

void cw::simulation::debug::opengl::drawer::drawContactPoint(const btVector3& PointOnB,
															 const btVector3& normalOnB,
															 btScalar distance,
															 int lifeTime,
															 const btVector3& color){

	btVector3 to= PointOnB+normalOnB*1;//distance;
	const btVector3&from = PointOnB;
	glColor4f(color.getX(), color.getY(), color.getZ(),1.f);
	//glColor4f(0,0,0,1.f);
	glBegin(GL_LINES);
	glVertex3d(from.getX(), from.getY(), from.getZ());
	glVertex3d(to.getX(), to.getY(), to.getZ());
	glEnd();

//		glRasterPos3f(from.x(),  from.y(),  from.z());
//		char buf[12];
//		sprintf(buf," %d",lifeTime);
	//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);

}

void cw::simulation::debug::opengl::drawer::reportErrorWarning(const char* warning_string){
	std::cout << warning_string << std::endl;
}

void cw::simulation::debug::opengl::drawer::draw3dText(const btVector3& location,
													   const char* textString){

	glRasterPos3f(location.x(),  location.y(),  location.z());

}

void cw::simulation::debug::opengl::drawer::setDebugMode(int mode){
	debug_mode = mode;
}

int cw::simulation::debug::opengl::drawer::getDebugMode() const {
	return debug_mode;
}

