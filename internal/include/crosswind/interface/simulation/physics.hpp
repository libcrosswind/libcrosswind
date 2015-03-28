#pragma once

#include <memory>

#include <crosswind/interface/simulation/detail/character.hpp>
#include <crosswind/interface/simulation/detail/body.hpp>

namespace cw{
namespace interface{
namespace simulation{

	class physics;

}// namespace simulation
}// namespace interface
}// namespace cw

class cw::interface::simulation::physics{
public:

	enum PRIMITIVE_PROXY{
		BOX    = 0,
		SPHERE = 1,
		PLANE  = 2
	};

	physics(const glm::vec3& c_gravity,
			const glm::vec3& c_scale,
			const glm::vec3& c_unit_value):
		gravity(c_gravity),
		scale(c_scale),
		unit_value(c_unit_value){

	}

	virtual void set_scale(const glm::vec3& new_scale) = 0;
	virtual glm::vec3 get_scale() = 0;

	virtual void set_gravity(const glm::vec3& new_gravity) = 0;
	virtual glm::vec3 get_gravity() = 0;

	virtual void debug_draw_world(const glm::mat4& projection_matrix) = 0;

	virtual void update(float dt) = 0;

	virtual std::shared_ptr<detail::character>
			create_character(const glm::vec3& origin, const glm::vec2& size, const float& step_height) = 0;


	virtual void add_character(std::shared_ptr<detail::character> character_ptr) = 0;
	virtual void remove_character(std::shared_ptr<detail::character> character_ptr) = 0;

	virtual std::shared_ptr<detail::body> create_primitive(const PRIMITIVE_PROXY& proxy_type,
			   									           const glm::vec3& origin,
			                                               const glm::vec3& size,
			                                               const float& mass) = 0;

	virtual void add_rigid_body(std::shared_ptr<detail::body> body_ptr) = 0;
	virtual void remove_rigid_body(std::shared_ptr<detail::body> body_ptr) = 0;

	virtual int get_collision_manifolds_number() = 0;
	virtual btPersistentManifold* get_manifold_by_index(const int& index) = 0;

protected:
	glm::vec3 gravity;
	glm::vec3 scale;
	glm::vec3 unit_value;

};// class physics