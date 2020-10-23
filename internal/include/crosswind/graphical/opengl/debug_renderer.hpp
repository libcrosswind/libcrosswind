#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <memory>

#include "glm/glm.hpp"

// forward declarations
namespace cw {
    namespace graphical {
        namespace object {

            class sprite;

        }// namespace object
    }// namespace graphical
}// namespace cw

namespace cw {
    namespace graphical {
        namespace opengl {

            class sprite_batch;
            class shader_program;

        }// namespace opengl
    }// namespace graphical
}// namespace cw

namespace cw {
    namespace simulation {
        namespace debug {
            namespace opengl {
                class simulation_shader_program;
            }
        }
    }
}

namespace cw {
    namespace graphical {
        namespace opengl {

            class debug_renderer {
            public:
                debug_renderer();
                ~debug_renderer();

                void set_uniform_matrix(const glm::mat4& value);

                void draw_line(const glm::ivec3& from, const glm::ivec3& to, const glm::vec3& color);
                
                void debug_draw(const glm::vec4& rect);

                void enqueue(const glm::ivec3& from, const glm::ivec3& to, const glm::vec3& color);
                void flush();

            private:
                std::vector<std::tuple<glm::ivec3, glm::ivec3, glm::vec3> > render_queue;
                glm::mat4 perspective;
                std::shared_ptr<cw::simulation::debug::opengl::simulation_shader_program> debug_shader_program;

                uint32_t debug_vbo_id;
            };

        }// namespace opengl
    }// namespace graphical
}// namespace cw
