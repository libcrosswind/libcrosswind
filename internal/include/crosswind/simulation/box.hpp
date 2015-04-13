#pragma once

#include "glm/glm.hpp"

#include "crosswind/simulation/detail/body.hpp"

namespace cw{
namespace simulation{

class box: public detail::body{
public:
    box(const glm::vec3& c_origin,
        const glm::vec3& c_size,
        const float&     c_mass,
        const glm::vec3& c_scale      = glm::vec3(1.0f, 1.0f, 1.0f),
        const glm::vec3& c_unit_value = glm::vec3(1.0f, 1.0f, 1.0f));

};// class box

}// namespace simulation
}// namespace cw
