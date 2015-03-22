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

	template<typename T>
	auto create_character(const glm::vec3& origin, const glm::vec2& size, const float& step_height){
		auto character = std::make_shared<T>(origin, size, step_height);
		add_character(character);
		return character;
	}

	virtual void add_character(std::shared_ptr<detail::character> character_ptr) = 0;
	virtual void remove_character(std::shared_ptr<detail::character> character_ptr) = 0;

	template<typename T>
	auto create_body(const glm::vec3& origin, const glm::vec3& size, const float& mass){
		auto body = std::make_shared<T>(origin, size, mass, scale, unit_value);
		add_rigid_body(body);
		return body;
	}

	virtual void add_body(std::shared_ptr<detail::body> body_ptr) = 0;
	virtual void remove_body(std::shared_ptr<detail::body> body_ptr) = 0;

protected:
	glm::vec3 gravity;
	glm::vec3 scale;
	glm::vec3 unit_value;

};// class physics