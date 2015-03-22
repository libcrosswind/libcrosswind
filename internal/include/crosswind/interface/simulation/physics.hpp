#pragma once

#include <memory>

namespace cw{
namespace interface{
namespace simulation{

	class physics;

}// namespace simulation
}// namespace interface
}// namespace cw

class cw::interface::simulation::world{
public:
	world(const glm::vec3& g, const glm::vec3& s, const glm::vec3& u): gravity(g), scale(s), unit_value(u){

	}

	virtual void set_scale(const glm::vec3& new_scale) = 0;
	virtual glm::vec3 get_scale() = 0;

	virtual void set_gravity(const glm::vec3& g) = 0;
	virtual void get_gravity() = 0;

	virtual void init_debug_drawer(auto camera) = 0;
	virtual void debug_draw_world() = 0;

	virtual void update(double dt) = 0;

	template<typename T>
	auto create_rigid_body(const glm::vec3& origin, const glm::vec3& size, const float& mass){
		auto body = std::make_shared<T>(origin, size, mass, scale, unit_value);
		add_rigid_body(body);
		return body;
	}

	virtual void add_rigid_body(std::shared_ptr<detail::rigid_body> body) = 0;
	virtual void remove_rigid_body(std::shared_ptr<detail::rigid_body> body) = 0;

	template<typename T>
	auto create_character(const glm::vec3& origin, const glm::vec2& size, const float& step_height){
		auto character = std::make_shared<T>(origin, size, step_height);
		add_character(character);
		return character;
	}

	virtual void add_character(std::shared_ptr<kinematic_character> character) = 0;
	virtual void remove_character(std::shared_ptr<kinematic_character> character) = 0;


protected:
	glm::vec3 gravity;
	glm::vec3 scale;
	glm::vec3 unit_value;

};// class dynamic_world