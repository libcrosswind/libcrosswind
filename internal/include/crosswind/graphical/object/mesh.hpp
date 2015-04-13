#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "crosswind/graphical/object/vertex.hpp"

namespace cw{
namespace graphical{
namespace object{

class mesh{
public:
    mesh(const glm::vec3& o, const glm::vec3& s);

    virtual void set_size(const glm::vec3& new_size);
    
    glm::vec3 get_size();

    virtual void set_origin(const glm::vec3& new_origin);

    glm::vec3 get_origin();

    void set_vertices(const std::vector<vertex>& new_vertices);

    std::vector<vertex>& get_vertices();

protected:
    glm::vec3 origin;
    glm::vec3 size;
    std::vector<vertex> vertices;

};// class mesh

}// namespace object
}// namespace graphical
}// namespace cw
