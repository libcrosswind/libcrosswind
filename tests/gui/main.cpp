#include <crosswind/platform/application.hpp>

class green_hill_zone: public cw::simulation::stage{
public:
    green_hill_zone(){

        this->name = "green_hill_zone";

    }

    virtual void init(std::shared_ptr<cw::platform::backend::interface::engine> engine){

        engine->mixer->load_music("green_hill", "green_hill_zone_bgm.ogg");
        engine->mixer->load_effect("jump", "Jump.wav");

        auto sonic_model  = engine->image->load_model(glm::vec3(0, 80, 0), glm::vec3( 40,  42, 10), "sonic.json");
        auto ground_model = engine->image->load_model(glm::vec3(0,  0, 0), glm::vec3(256, 256, 10), "ground.json");

        sonic_body =
                engine->physics->create_rigid_body<cw::physics::box>(glm::vec3(0, 100, 0), glm::vec3(40, 42, 10), 1.0);

        sonic_body->set_activation_policy(DISABLE_DEACTIVATION);
        sonic_body->set_linear_factor(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));


        glm::vec3 ground_offset = ground_model->get_origin();
        ground_offset.y = -96;

        ground_body =
                engine->physics->create_rigid_body<cw::physics::box>(ground_offset,
                        glm::vec3(256, 64, 10),
                        0);

        ground_body->set_linear_factor(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));


        sonic_model->attach_rigid_body("sonic_body", sonic_body, true);
        ground_model->attach_rigid_body("ground_body", ground_body, false);

        this->conditions["jumping"] = false;

        post_event([this, engine, sonic_model](){
            if(engine->input_listener->is_key_down("k")){

                if(this->conditions["jumping"] == false){

                    this->sonic_body->set_linear_speed(glm::vec3(0.0f, 6.5f, 0.0f));
                    sonic_model->change_animation("roll_1");
                    engine->mixer->play_effect("jump");
                    this->conditions["jumping"] = true;
                }

            } else {

                if(this->conditions["jumping"] == true){
                    sonic_model->change_animation("stand");
                    this->conditions["jumping"] = false;
                }

            }

/*            if(engine->input_listener->is_key_down("Right")){


                float acc = 0.046875 / 0.026458f;

                auto spd = this->sonic_body->get_linear_speed();

                spd.x += acc;

                this->sonic_body->set_linear_speed(spd);
                sonic_model->change_animation("walk");


            } else {

                float frc = 0.046875 / 0.026458f;

                auto spd = this->sonic_body->get_linear_speed();

                spd.x -= frc;

                if(spd.x < 0){
                    spd.x = 0;
                }

                this->sonic_body->set_linear_speed(spd);

            }
*/


        }, true);



        engine->physics->add_rigid_body(sonic_body);
        engine->physics->add_rigid_body(ground_body);




        add("sonic",  sonic_model);
        add("ground", ground_model);

    }

    virtual void deinit(std::shared_ptr<cw::platform::backend::interface::engine> engine){
        engine->physics->remove_rigid_body(sonic_body);
        engine->physics->remove_rigid_body(ground_body);
    }

private:
    std::shared_ptr<cw::physics::box> sonic_body;
    std::shared_ptr<cw::physics::box> ground_body;
};

int main(int argc, char **argv) {

    cw::platform::filesystem::add_directory("assets", true);

    auto window_bounds = glm::vec4(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    auto app = std::make_shared<cw::platform::application>("Main Window", window_bounds);

    app->add_stage(std::make_shared<green_hill_zone>());
    app->swap_stage("current", "green_hill_zone");
    app->run();


    return 0;
}