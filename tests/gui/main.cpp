#include <glm/glm.hpp>

#include <crosswind/platform/application.hpp>
#include <crosswind/platform/filesystem.hpp>
#include <crosswind/platform/sdl/sdl_surface.hpp>

#include <crosswind/simulation/sprite.hpp>
#include <crosswind/simulation/gl/glsl_program.hpp>
#include <crosswind/simulation/gl/gl_texture.hpp>

#include <iostream>


int main(int argc, char **argv) {
    cw::platform::filesystem::add_directory("assets", true);

    auto app = std::make_shared<cw::platform::application>();
    app->init({SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480});

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

            std::unique_ptr<cw::platform::sdl::sdl_surface> sonic_texture_surface =
            std::make_unique<cw::platform::sdl::sdl_surface>(cw::platform::filesystem::get_file_path("blue_button_spritesheet.png"));

            auto data_ptr = sonic_texture_surface->data.acquire();
            sonic_texture = std::make_shared<cw::simulation::gl::gl_texture>
                    (glm::vec2(data_ptr->w, data_ptr->h), data_ptr->format->BytesPerPixel, data_ptr->pixels);
            sonic_texture_surface->data.release();


/*
            btn_stand = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            btn_walk  = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            btn_run   = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            btn_play_audio = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            sonic = std::make_shared<cw::simulation::standard_image>(pos, dim);

            add(btn_stand);
            add(btn_walk);
            add(btn_run);
            add(btn_play_audio);
            add(sonic);*/

            simple_sprite = std::make_shared<cw::simulation::sprite>
                    (glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

            add(simple_sprite);
        }

        virtual void init(std::shared_ptr<cw::platform::sdl::sdl_audio_system> sdl_audio_system){

//            sdl_audio_system->load_music("marble", cw::platform::filesystem::get_file_path("marble_zone_bgm.ogg"));
//            sdl_audio_system->play_music("marble");

//            sdl_audio_system->load_effect("jump", cw::platform::filesystem::get_file_path("Jump.wav"));
//            sdl_audio_system->play_effect("jump");

/*            btn_stand->init(sdl_renderer, "blue_button.json");
            btn_walk->init(sdl_renderer, "blue_button.json");
            btn_run->init(sdl_renderer, "blue_button.json");
            btn_play_audio->init(sdl_renderer, "blue_button.json");
            sonic->init(sdl_renderer, "sonic.json");

            btn_stand->on_mouse_down += [this](){
                post_event([this](){
                    this->sonic->swap_graphical_item(this->sonic->animations, "current", "stand");
                });
            };

            btn_walk->on_mouse_down += [this](){
                post_event([this](){
                    this->sonic->swap_graphical_item(this->sonic->animations, "current", "walk");
                });
            };

            btn_run->on_mouse_down += [this](){
                post_event([this](){
                    this->sonic->swap_graphical_item(this->sonic->animations, "current", "run");
                });
            };

            btn_play_audio->on_mouse_down += [this, sdl_audio_system](){
                this->post_event([sdl_audio_system](){
                    sdl_audio_system->play_music("marble");
                });
            };*/
        }

        virtual void render() override {

            auto& container = graphical_queue.data.acquire();
            glsl_program->use();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sonic_texture->id);

            auto texture_location = glsl_program->get_uniform_location("texture_sampler");
            glUniform1i(texture_location, 0);

            for(auto& element: container){
                element->draw();
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            glsl_program->unuse();
            graphical_queue.data.release();

        }


    private:
/*        std::shared_ptr<cw::simulation::interactive_image> btn_stand;
        std::shared_ptr<cw::simulation::interactive_image> btn_walk;
        std::shared_ptr<cw::simulation::interactive_image> btn_run;
        std::shared_ptr<cw::simulation::interactive_image> btn_play_audio;

        std::shared_ptr<cw::simulation::standard_image> sonic;*/

        std::shared_ptr<cw::simulation::sprite> simple_sprite;
        std::shared_ptr<cw::simulation::gl::gl_texture> sonic_texture;
        std::shared_ptr<cw::simulation::gl::glsl_program> glsl_program;
    };

    app->add_stage(std::make_shared<marble_zone>());
    app->swap_stage("current", "marble_zone");
    app->run();

    return 0;
}