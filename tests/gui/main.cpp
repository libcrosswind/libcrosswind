#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <crosswind/physics/box.hpp>

#include <crosswind/platform/application.hpp>
#include <crosswind/platform/filesystem.hpp>
#include <crosswind/platform/sdl/sdl_surface.hpp>

#include <crosswind/simulation/actor.hpp>
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


    class green_hill_zone: public cw::simulation::stage{
    public:
        green_hill_zone(){

            this->name.set("green_hill_zone");

            glsl_program = std::make_shared<cw::simulation::gl::glsl_program>();
            std::string vertex_shader = "assets/default/graphics/shaders/texture_shading.vert";
            std::string fragment_shader = "assets/default/graphics/shaders/texture_shading.frag";

            glsl_program->compile(vertex_shader, fragment_shader);
            glsl_program->add_attribute("vertex_position");
            glsl_program->add_attribute("vertex_color");
            glsl_program->add_attribute("vertex_uv");
            glsl_program->link();

            camera_list["current"] = std::make_shared<cw::simulation::camera>(640, 480);
            batch_list["current"] = std::make_shared<cw::simulation::gl::gl_sprite_batch>();


            load_texture("sonic_wait", "SonAni_Wait_intro.png");
            load_texture("sonic_walk", "SonAni_Walk.png");
            load_texture("sonic_run", "SonAni_Run.png");
            load_texture("sonic_roll", "SonAni_Roll.png");

            load_texture("ground", "60.png");

            actor_list["sonic"]  = std::make_shared<cw::simulation::actor>();
            actor_list["ground"] = std::make_shared<cw::simulation::actor>();


            float horizontal_offset = 0.0f;
            for(int i = 0; i<1; i++){

                actor_list["ground"]->sprites["tile_" + std::to_string(i)] = std::make_shared<cw::simulation::sprite>
                        (glm::vec3(-320.5f + horizontal_offset, -240.0f, 1.0f),
                                glm::vec3(256.0f,256.0f,0.0f),
                                glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                                texture_list["ground"]->id,
                                0.0f);

                horizontal_offset += 256;
            }

            actor_list["ground"]->rigid_body =
                    std::make_shared<cw::physics::box>(0.0f,
                            glm::vec3(-320.5f, -240.0f, 1.0f),
                            glm::vec3(256.0f,66,1.0f));





            actor_list["sonic"]->sprites["stand"] = std::make_shared<cw::simulation::sprite>
                                                        (glm::vec3(-310.0f, 120.0f, 1.0f),
                                                                glm::vec3(48, 48,0.0f),
                                                                glm::vec4(0.0f, 0.0f, 0.2f, 1.0f),
                                                                texture_list["sonic_wait"]->id,
                                                                0.0f);

            actor_list["sonic"]->rigid_body = std::make_shared<cw::physics::box>(20.0f,
                    glm::vec3(-310.0f, 120.0f, 1.0f), glm::vec3(48, 48,0.0f));


            add(batch_list["current"]);
            add(camera_list["current"]);
            add(actor_list["sonic"]);
            add(actor_list["ground"]);
        }

        void load_texture(const std::string& name, const std::string& path){
            auto surface = std::make_unique<cw::platform::sdl::sdl_surface>(cw::platform::filesystem::get_file_path(path));


            texture_list[name] = std::make_shared<cw::simulation::gl::gl_texture>
                    (glm::vec2(surface->data.ptr()->w, surface->data.ptr()->h),
                            surface->data.ptr()->format->BytesPerPixel,
                            surface->data.ptr()->pixels);

        }

        virtual void init(std::shared_ptr<cw::physics::dynamic_world> world,
                          std::shared_ptr<cw::platform::sdl::sdl_audio_system> sdl_audio_system){


            sdl_audio_system->load_music("green_hill", cw::platform::filesystem::get_file_path("green_hill_zone_bgm.ogg"));
            sdl_audio_system->play_music("green_hill");

/*
            sdl_audio_system->load_effect("jump", cw::platform::filesystem::get_file_path("Jump.wav"));
            sdl_audio_system->play_effect("jump");*/


            world->add_rigid_body(actor_list["ground"]->rigid_body);
            world->add_rigid_body(actor_list["sonic"]->rigid_body);

        }

        virtual void deinit(std::shared_ptr<cw::physics::dynamic_world> world){
            world->remove_rigid_body(actor_list["ground"]->rigid_body);
            world->remove_rigid_body(actor_list["sonic"]->rigid_body);
        }


        virtual void render() override {

            glsl_program->use();

            glActiveTexture(GL_TEXTURE0); //Need to integrate this into batch list or program keymap

            auto texture_location = glsl_program->get_uniform_location("texture_sampler");
            glUniform1i(texture_location, 0);

            auto projection_matrix_location = glsl_program->get_uniform_location("projection_matrix");
            auto camera_matrix = camera_list["current"]->get_camera_matrix();

            glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(camera_matrix));

            batch_list["current"]->begin();

            for(auto& actor_mapping : actor_list){
                for(auto& sprite_mapping : actor_mapping.second->sprites){
                    batch_list["current"]->upload(sprite_mapping.second);
                }
            }

            batch_list["current"]->end();

            auto& container = graphical_queue.data.acquire();

            for(auto& element: container){
                element->draw();
            }

            graphical_queue.data.release();

            glsl_program->unuse();

        }

    private:
        std::map<std::string, std::shared_ptr<cw::simulation::camera> > camera_list;
        std::map<std::string, std::shared_ptr<cw::simulation::actor> >  actor_list;
        std::map<std::string, std::shared_ptr<cw::simulation::gl::gl_sprite_batch>  > batch_list;
        std::map<std::string, std::shared_ptr<cw::simulation::gl::gl_texture> > texture_list;

        std::shared_ptr<cw::simulation::gl::glsl_program> glsl_program;
    };

    app->add_stage(std::make_shared<green_hill_zone>());
    app->swap_stage("current", "green_hill_zone");
    app->run();

    return 0;
}