#pragma once

#include <string>
#include <memory>

#include "glm/glm.hpp"

// forward declarations
namespace cw{
namespace graphical{
namespace object{

    class sprite;

}// namespace object
}// namespace graphical
}// namespace cw

namespace cw{
namespace graphical{
namespace opengl{

    class sprite_batch;
    class shader_program;

}// namespace opengl
}// namespace graphical
}// namespace cw

namespace cw{
namespace graphical{
namespace opengl{

class renderer{
public:
	renderer();

    void begin();

    void set_uniform_matrix(const std::string& uniform_matrix_name, const glm::mat4& value);

    void upload(std::shared_ptr<object::sprite> render_sprite);

    void draw();

    void end();

private:
    std::shared_ptr<sprite_batch> sprite_batch;
    std::shared_ptr<shader_program> shader_program;

};

}// namespace opengl
}// namespace graphical
}// namespace cw
