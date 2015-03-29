#pragma once

#include <glm/glm.hpp>

#include <crosswind/interface/simulation/debug/shader_program.hpp>

namespace cw{
namespace interface{
namespace simulation{
namespace debug{

	class drawer;

}// namespace debug
}// namespace simulation
}// namespace interface
}// namespace cw


class cw::interface::simulation::debug::drawer{
public:
	drawer(){
	}

	virtual ~drawer(){
	}

	virtual void update(const glm::mat4& f_perspective, const glm::vec3& f_scale) = 0;


private:
    std::shared_ptr<shader_program> shader_program;
	glm::mat4 perspective;
	glm::vec3 scale;
};
