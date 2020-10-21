#pragma once

#include <memory>

#include "bullet/btBulletDynamicsCommon.h"
#include "glm/glm.hpp"


// forward declarations
namespace cw{
namespace simulation{
namespace detail{
	
	class character;
	class body;

}// namespace detail
}// namespace simulation
}// namespace cw

namespace cw{
namespace simulation{
namespace debug{
namespace opengl{
	
	class drawer;

}// namespace opengl
}// namespace debug
}// namespace simulation
}// namespace cw


namespace cw{
namespace simulation{

class physics{
public:
	enum PRIMITIVE_PROXY{
		BOX    = 0,
		SPHERE = 1,
		PLANE  = 2
	};

	physics(const glm::vec3& c_gravity,
			const glm::vec3& c_scale,
			const glm::vec3& c_unit_value);

	void set_scale(const glm::vec3& new_scale);

	glm::vec3 get_scale();

	void set_gravity(const glm::vec3& new_gravity);

	glm::vec3 get_gravity();

	void debug_draw_world(const glm::mat4& projection_matrix);

	void update(float dt);

	std::shared_ptr<detail::character> create_character(const glm::vec3& origin,
														 const glm::vec2& size,
														 const float& step_height);

	void add_character(std::shared_ptr<detail::character> character_ptr);

	void remove_character(std::shared_ptr<detail::character> character_ptr);

	std::shared_ptr<detail::body> create_primitive(const PRIMITIVE_PROXY& proxy_type,
												   const glm::vec3& origin,
												   const glm::vec3& size,
												   const float& mass);


	void add_rigid_body(std::shared_ptr<detail::body> body_ptr);

	void remove_rigid_body(std::shared_ptr<detail::body> body_ptr);

	int get_collision_manifolds_number();

	btPersistentManifold* get_manifold_by_index(const int& index);

private:
	glm::vec3 gravity;
	glm::vec3 scale;
	glm::vec3 unit_value;
	std::unique_ptr<btDynamicsWorld> 			world;
	std::unique_ptr<btConstraintSolver> 		solver;
	std::unique_ptr<btBroadphaseInterface> 		broad_phase;
	std::unique_ptr<btDispatcher>    			dispatcher;
	std::unique_ptr<btCollisionConfiguration>	collision_config;
	std::shared_ptr<debug::opengl::drawer>  	drawer;

};// class physics

}// namespace simulation
}// namespace cw