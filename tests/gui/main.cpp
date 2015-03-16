#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <crosswind/physics/box.hpp>

#include <crosswind/platform/application.hpp>
#include <crosswind/platform/filesystem.hpp>

#include <crosswind/simulation/model.hpp>
#include <crosswind/simulation/sprite.hpp>
#include <crosswind/simulation/camera.hpp>
#include <crosswind/simulation/gl/glsl_program.hpp>
#include <crosswind/simulation/gl/gl_sprite_batch.hpp>


int main(int argc, char **argv) {


    cw::platform::filesystem::add_directory("assets", true);

    auto window_bounds = glm::vec4(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    auto app = std::make_shared<cw::platform::application>("Main Window", window_bounds);


    class green_hill_zone: public cw::simulation::stage{
    public:
        green_hill_zone(){

            this->name.set("green_hill_zone");

        }

        virtual void init(std::shared_ptr<cw::platform::backend::interface::engine> engine){

            engine->mixer->load_music("green_hill", "green_hill_zone_bgm.ogg");
            engine->mixer->play_music("green_hill");

            engine->mixer->load_effect("jump", "Jump.wav");
        //    engine->mixer->play_effect("jump");
            // Sonic gravity is -0.21875f per step, we have 60 steps per second.
            float g = -13.125 / 0.026458f;
            float a = 224/480;

            g += g + a * g;
            engine->physics_world->set_unit_value(glm::vec3(1.0f, 0.00026458f, 1.0f));
            engine->physics_world->set_world_ratio(glm::vec3(1.0f, 0.00026458f, 1.0f));
            engine->physics_world->set_gravity(glm::vec3(0.0f, g, 0.0f));


            camera_list["current"] = std::make_shared<cw::simulation::camera>(640, 480);

            engine->image->load_texture("sonic_wait", "SonAni_Wait_intro.png");
            engine->image->load_texture("sonic_walk", "SonAni_Walk.png");
            engine->image->load_texture("sonic_run", "SonAni_Run.png");
            engine->image->load_texture("sonic_roll", "SonAni_Roll.png");

            engine->image->load_texture("ground", "60.png");

            auto sonic_model  = std::make_shared<cw::simulation::model>();
            auto ground_model = std::make_shared<cw::simulation::model>();

            auto ground_sprite = std::make_shared<cw::simulation::sprite>
                                 (glm::vec3(0.0f, -100.0f, 1.0f),                 // position
                                  glm::vec3(256.0f, 256.0f, 256.0f),              // size
                                  glm::vec4(0.0f, 0.0f, 1.0f, 1.0),               // uv
                                  engine->image->load_texture("ground")->id);     // texture id

            auto ground_body   = engine->physics_world->create<cw::physics::box>
                                 (0.0f,                                           // mass
                                  glm::vec3(0.0f, -196.0f, 1.0f),                 // position
                                  glm::vec3(256.0f, 64.0f, 256.0f));              // size

            auto stand_sprite  = std::make_shared<cw::simulation::sprite>
                                 (glm::vec3(0.0f, 0.0f, 1.0f),                    // position
                                  glm::vec3(48, 48, 48.0f),                       // size
                                  glm::vec4(0.0f, 0.0f, 0.2f, 1.0f),              // uv
                                  engine->image->load_texture("sonic_wait")->id); // texture id

            auto sonic_body    = engine->physics_world->create<cw::physics::box>
                                 (1.0f,                                           // mass
                                  glm::vec3(0.0f, 50.0f, 1.0f),                  // position
                                  glm::vec3(48.0f, 48.0f, 48.0f));                // size

            sonic_body->set_activation_policy(DISABLE_DEACTIVATION);

            sonic_model->add_sprite("stand_sprite", stand_sprite);
            sonic_model->add_body("sonic_body", sonic_body);
            sonic_model->constrain("stand_sprite", "sonic_body");

            ground_body->set_linear_factor(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            sonic_body->set_linear_factor(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

            ground_model->add_sprite("ground_sprite", ground_sprite);
            ground_model->add_body("ground_body", ground_body);

            model_list["sonic"] = sonic_model;
            model_list["ground"] = ground_model;
            add(batch_list["current"]);
            add(camera_list["current"]);
            add(model_list["sonic"]);
            add(model_list["ground"]);

            engine->physics_world->add_rigid_body(model_list["ground"]->rigid_bodies["ground_body"]);
            engine->physics_world->add_rigid_body(model_list["sonic"]->rigid_bodies["sonic_body"]);

            engine->physics_world->init_debug_drawer(camera_list["current"]);

            this->conditions["jumping"] = false;


            post_event([this, engine](){
               if(engine->input_listener->is_key_down("k")){

                   if(this->conditions["jumping"] == false){

                       float pixels = 6.5f / 0.026458f;
                       float aspect = 224/480;

                       pixels += pixels + aspect * pixels;
                       this->model_list["sonic"]->rigid_bodies["sonic_body"]->set_linear_speed(glm::vec3(0.0f, pixels, 0.0f));
//                       this->model_list["sonic"]->rigid_bodies["sonic_body"]->apply_force(glm::vec3(0.0f, 1.0f, 0.0f));
                       engine->mixer->play_effect("jump");
                       this->conditions["jumping"] = true;
                   }

               } else {

                   if(this->conditions["jumping"] == true){
//                       this->model_list["sonic"]->rigid_bodies["sonic_body"]->set_linear_speed(glm::vec3(0.0f, -6.5f, 0.0f));
//                       this->model_list["sonic"]->rigid_bodies["sonic_body"]->apply_force(glm::vec3(0.0f, -1.0f, 0.0f));
                       this->conditions["jumping"] = false;
                   }

               }
            }, true);

        }

        virtual void deinit(std::shared_ptr<cw::platform::backend::interface::engine> engine){
            engine->physics_world->remove_rigid_body(model_list["ground"]->rigid_bodies["ground_body"]);
            engine->physics_world->remove_rigid_body(model_list["sonic"]->rigid_bodies["sonic_body"]);
        }

        virtual void render() override {


            auto& container = graphical_queue.data.acquire();

            for(auto& element: container){
                element->draw();
            }

            graphical_queue.data.release();


        }

    private:
        std::map<std::string, std::shared_ptr<cw::simulation::camera> >                 camera_list;
        std::map<std::string, std::shared_ptr<cw::simulation::model> >                  model_list;

    };

    app->add_stage(std::make_shared<green_hill_zone>());
    app->swap_stage("current", "green_hill_zone");
    app->run();

    return 0;
}