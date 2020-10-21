#pragma once

#include <memory>

#include "bullet/btBulletDynamicsCommon.h"
#include "glm/glm.hpp"

namespace cw{
namespace simulation{
namespace detail{
 
class body{

public:
	body(const glm::vec3& c_origin, 
		 const glm::vec3& c_scale      = glm::vec3(1.0f, 1.0f, 1.0f), 
		 const glm::vec3& c_unit_value = glm::vec3(1.0f, 1.0f, 1.0f));

	void init(const float& mass, btMotionState* state, btCollisionShape* shape);

    void set_origin(const glm::vec3& new_origin);

	glm::vec3 get_origin();

	void set_linear_speed(const glm::vec3& speed);

	glm::vec3 get_linear_speed();

	void apply_force(const glm::vec3& new_force);

	void set_activation_policy(int policy);

	void set_linear_factor(const glm::vec3& position, const glm::vec3& rotation);

	std::unique_ptr<btMotionState> motion_state;
	std::unique_ptr<btCollisionShape> collision_shape;
	std::unique_ptr<btRigidBody> physic_body;

protected:
    glm::vec3 origin;
    glm::vec3 scale;
    glm::vec3 unit_value;

};// class body

}// namespace detail
}// namespace simulation
}// namespace cw