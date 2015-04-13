#pragma once

#include "glm/glm.hpp"

#include "crosswind/physics/detail/rigid_body.hpp"

namespace cw{
namespace physics{
	
class plane: public detail::rigid_body{
public:
	plane(const glm::vec3& origin,
          const glm::vec3& size, 
          const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

};// class plane

}// namespace physics
}// namespace cw