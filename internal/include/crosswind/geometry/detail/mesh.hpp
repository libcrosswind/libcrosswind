#pragma once

#include <vector>
#include <utility>

#include <glm/glm.hpp>

#include <crosswind/geometry/detail/vertex.hpp>

namespace cw{
namespace geometry{
namespace detail{

    class mesh;

}// namespace detail
}// namespace geometry
}// namespace cw

class cw::geometry::detail::mesh{
public:
    mesh(const glm::vec3& p, const glm::vec3& s):
        origin(p), size(s){

    }

    std::vector<vertex> vertices;

protected:
    glm::vec3 origin;
    glm::vec3 size;
};// class mesh