#pragma once

#include <glm/glm.hpp>

namespace cw{
namespace interface{
namespace simulation{
namespace detail{

	class body;

}// namespace detail
}// namespace simulation
}// namespace interface
}// namespace cw

class cw::interface::simulation::detail::body{

public:
	body(const glm::vec3& c_origin, 
		 const glm::vec3& c_scale      = glm::vec3(1.0f, 1.0f, 1.0f), 
		 const glm::vec3& c_unit_value = glm::vec3(1.0f, 1.0f, 1.0f)): 
	origin(c_origin),
	scale(c_scale), 
	unit_value(c_unit_value){

	}

    virtual void set_origin(const glm::vec3& origin) = 0;
    virtual glm::vec3 get_origin() = 0;

	virtual void set_linear_speed(const glm::vec3& speed) = 0;
	virtual glm::vec3 get_linear_speed() = 0;

	virtual void apply_force(const glm::vec3& f) = 0;


	void set_activation_policy(auto state){
		physic_body->setActivationState(state);
	}

	void set_linear_factor(const glm::vec3& position, const glm::vec3& rotation){
		physic_body->setLinearFactor(btVector3(position.x, position.y, position.z));
		physic_body->setAngularFactor(btVector3(rotation.x, rotation.y, rotation.z));
	}

	std::unique_ptr<btMotionState> motion_state;
	std::unique_ptr<btCollisionShape> collision_shape;
	std::unique_ptr<btRigidBody> physic_body;

protected:
    glm::vec3 origin;
    glm::vec3 scale;
    glm::vec3 unit_value;

};// class body