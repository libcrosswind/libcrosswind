#pragma once

#include <memory>
#include <cstdint>
#include <vector>

#include "bullet/LinearMath/btIDebugDraw.h"
#include "glm/glm.hpp"

#include "crosswind/simulation/debug/opengl/simulation_vertex.hpp"

// forward declarations
namespace cw{
namespace simulation{
namespace debug{
namespace opengl{	

	class simulation_shader_program;

}// namespace opengl
}// namespace debug
}// namespace simulation
}// namespace cw

namespace cw{
namespace simulation{
namespace debug{
namespace opengl{

class drawer: public btIDebugDraw{
public:
	drawer();

	~drawer();

	void update(const glm::mat4& f_perspective, const glm::vec3& f_scale);

	void upload_vertex_array(const std::vector<simulation_vertex>& vertex_array);

	virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& fromColor, const btVector3& toColor);

	virtual void drawLine(const btVector3& f,const btVector3& t,const btVector3& color);

	virtual void drawSphere (const btVector3& p, btScalar radius, const btVector3& color);

	virtual void drawTriangle(const btVector3& a, 
							  const btVector3& b, 
							  const btVector3& c, 
							  const btVector3& color, 
							  btScalar alpha);

	virtual void drawContactPoint(const btVector3& PointOnB, 
								  const btVector3& normalOnB, 
								  btScalar distance, 
								  int lifeTime, 
								  const btVector3& color);

	virtual void reportErrorWarning(const char* warning_string);

	virtual void draw3dText(const btVector3& location,const char* textString);

	virtual void setDebugMode(int mode);

	virtual int getDebugMode() const;

private:
    std::shared_ptr<simulation_shader_program> shader_program;
	glm::mat4 perspective;
	glm::vec3 scale;
	int debug_mode;
	uint32_t vbo_id;

};// class drawer

}// namespace opengl
}// namespace debug
}// namespace simulation
}// namespace cw
