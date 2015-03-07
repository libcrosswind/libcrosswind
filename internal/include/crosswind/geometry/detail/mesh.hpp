#pragma once

#include <vector>
#include <utility>

#include <glm/glm.hpp>

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
    position(p), size(s){

    }

protected:
    std::vector<std::pair<glm::vec4, glm::vec4> > vertices; //first is position, second is color.
    glm::vec3 position;
    glm::vec3 size;
};// class mesh