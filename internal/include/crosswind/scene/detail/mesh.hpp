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
    mesh(const glm::vec3& o, const glm::vec3& s):
        origin(o), size(s){

    }

    virtual void set_size(const glm::vec3& new_size){ size = new_size; }
    virtual glm::vec3 get_size(){ return size; }

    virtual void set_origin(const glm::vec3& new_origin){ origin = new_origin; }
    virtual glm::vec3 get_origin(){ return origin; }

    virtual void set_vertices(const std::vector& new_vertices){ vertices = new_vertices; }
    virtual std::vector<vertex> get_vertices(){ return vertices; }

protected:
    glm::vec3 origin;
    glm::vec3 size;
    std::vector<vertex> vertices;

};// class mesh