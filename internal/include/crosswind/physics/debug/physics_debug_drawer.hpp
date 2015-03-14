#pragma once

#include "LinearMath/btIDebugDraw.h"


#include <stdio.h> //printf debugging


#include <crosswind/simulation/camera.hpp>
#include <crosswind/simulation/gl/gl_vbo.hpp>
#include <crosswind/simulation/gl/glsl_program.hpp>

namespace cw{
namespace physics{
namespace debug{

	class physics_debug_drawer;

}// namespace debug
}// namespace physics
}// namespace cw


class cw::physics::debug::physics_debug_drawer : public btIDebugDraw, public cw::simulation::gl::gl_vbo {
public:

	physics_debug_drawer(): debug_mode(btIDebugDraw::DBG_DrawWireframe){

		glsl_program = std::make_shared<cw::simulation::gl::glsl_program>();
		std::string vertex_shader   = "assets/default/graphics/shaders/primitive_shading.vert";
		std::string fragment_shader = "assets/default/graphics/shaders/primitive_shading.frag";

		glsl_program->compile(vertex_shader, fragment_shader);
		glsl_program->add_attribute("vertex_position");
		glsl_program->add_attribute("vertex_color");
		glsl_program->link();

	}

	virtual ~physics_debug_drawer(){

	}

	void init(std::shared_ptr<cw::simulation::camera> cam){
		camera = cam;
	}

	virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& fromColor, const btVector3& toColor){

	}

	virtual void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color){
		glsl_program->use();

		auto projection_matrix_location = glsl_program->get_uniform_location("projection_matrix");
		auto camera_matrix = camera->get_camera_matrix();

		glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(camera_matrix));

		glm::vec4 n_from(from.getX(), from.getY(), from.getZ(), 1.0);
		glm::vec4 n_to(to.getX(), to.getY(), to.getZ(),1.0);
		glm::vec4 c(color.getX(), color.getY(), color.getZ(), 1.0);
		glm::vec2 u(0.0, 0.0);

		std::vector<cw::geometry::detail::vertex> vertex_array;
		cw::geometry::detail::vertex a(n_from, c, u);
		cw::geometry::detail::vertex b(n_to, c, u);
		vertex_array.push_back(a);
		vertex_array.push_back(b);

		upload_vertex_array(vertex_array);

		glBindBuffer(GL_ARRAY_BUFFER, id);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0,
				4,
				GL_FLOAT,
				GL_FALSE,
				sizeof(cw::geometry::detail::vertex),
				(void*)offsetof(cw::geometry::detail::vertex, cw::geometry::detail::vertex::position));

		glVertexAttribPointer(1,
				4,
				GL_FLOAT,
				GL_FALSE,
				sizeof(cw::geometry::detail::vertex),
				(void*)offsetof(cw::geometry::detail::vertex, cw::geometry::detail::vertex::color));

		glDrawArrays( GL_POINTS, 0, vertex_array.size() );
		glDrawArrays( GL_LINES, 0, vertex_array.size() );


		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glsl_program->unuse();
	}

	virtual void	drawSphere (const btVector3& p, btScalar radius, const btVector3& color){

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

	virtual void	drawTriangle(const btVector3& a,const btVector3& b,const btVector3& c,const btVector3& color,btScalar alpha){
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

	virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color){
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
	virtual void	reportErrorWarning(const char* warningString){
		printf("%s\n",warningString);
	}

	virtual void	draw3dText(const btVector3& location,const char* textString){
		glRasterPos3f(location.x(),  location.y(),  location.z());
	}

	virtual void	setDebugMode(int mode){
		debug_mode = mode;
	}

	virtual int		getDebugMode() const {
		return debug_mode;
	}



private:
    std::shared_ptr<cw::simulation::gl::glsl_program> glsl_program;

	std::shared_ptr<cw::simulation::camera> camera;

	int debug_mode;
};

