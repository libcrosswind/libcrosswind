#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <crosswind/platform/application.hpp>
#include <crosswind/platform/filesystem.hpp>
#include <crosswind/platform/sdl/sdl_surface.hpp>

#include <crosswind/simulation/sprite.hpp>
#include <crosswind/simulation/camera.hpp>
#include <crosswind/simulation/gl/glsl_program.hpp>
#include <crosswind/simulation/gl/gl_texture.hpp>
#include <crosswind/simulation/gl/gl_sprite_batch.hpp>


#include <iostream>


int main(int argc, char **argv) {
    cw::platform::filesystem::add_directory("assets", true);

    auto window_bounds = glm::vec4(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    auto app = std::make_shared<cw::platform::application>("Main Window", window_bounds);

    class marble_zone: public cw::simulation::stage{
    public:
        marble_zone(){

            this->name.set("marble_zone");

            glsl_program = std::make_shared<cw::simulation::gl::glsl_program>();
//            std::string vertex_shader = "assets/default/graphics/shaders/primitive_shading.vert";
//            std::string fragment_shader = "assets/default/graphics/shaders/primitive_shading.frag";
            std::string vertex_shader = "assets/default/graphics/shaders/texture_shading.vert";
            std::string fragment_shader = "assets/default/graphics/shaders/texture_shading.frag";

            glsl_program->compile(vertex_shader, fragment_shader);
            glsl_program->add_attribute("vertex_position");
            glsl_program->add_attribute("vertex_color");
            glsl_program->add_attribute("vertex_uv");
            glsl_program->link();

            camera = std::make_shared<cw::simulation::camera>(640, 480);

            std::string surface_path = cw::platform::filesystem::get_file_path("blue_button_spritesheet.png");
            auto surface = std::make_unique<cw::platform::sdl::sdl_surface>(surface_path);

            sonic_texture = std::make_shared<cw::simulation::gl::gl_texture>
                    (glm::vec2(surface->data.ptr()->w, surface->data.ptr()->h),
                     surface->data.ptr()->format->BytesPerPixel,
                     surface->data.ptr()->pixels);

            simple_sprite = std::make_shared<cw::simulation::sprite>
                           (glm::vec3(-0.5f, -0.5f, 1.0f),
                            glm::vec3(640/2,480/2,0.0f),
                            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                            sonic_texture->id,
                            0.0f);

            sprite_batch = std::make_shared<cw::simulation::gl::gl_sprite_batch>();

            add(sprite_batch);
            add(camera);
        }

        virtual void init(std::shared_ptr<cw::platform::sdl::sdl_audio_system> sdl_audio_system){

//            sdl_audio_system->load_music("marble", cw::platform::filesystem::get_file_path("marble_zone_bgm.ogg"));
//            sdl_audio_system->play_music("marble");

//            sdl_audio_system->load_effect("jump", cw::platform::filesystem::get_file_path("Jump.wav"));
//            sdl_audio_system->play_effect("jump");

        }

        virtual void render() override {

            auto& container = graphical_queue.data.acquire();
            glsl_program->use();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sonic_texture->id);

            auto texture_location = glsl_program->get_uniform_location("texture_sampler");
            glUniform1i(texture_location, 0);

            auto projection_matrix_location = glsl_program->get_uniform_location("projection_matrix");
            auto camera_matrix = camera->get_camera_matrix();

            glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(camera_matrix));

            sprite_batch->begin();

            sprite_batch->upload(simple_sprite);

            sprite_batch->end();

            for(auto& element: container){
                element->draw();
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            glsl_program->unuse();
            graphical_queue.data.release();

        }


    private:
        std::shared_ptr<cw::simulation::camera> camera;
        std::shared_ptr<cw::simulation::sprite> simple_sprite;
        std::shared_ptr<cw::simulation::gl::gl_sprite_batch> sprite_batch;
        std::shared_ptr<cw::simulation::gl::gl_texture> sonic_texture;
        std::shared_ptr<cw::simulation::gl::glsl_program> glsl_program;
    };

    app->add_stage(std::make_shared<marble_zone>());
    app->swap_stage("current", "marble_zone");
    app->run();

    return 0;
}