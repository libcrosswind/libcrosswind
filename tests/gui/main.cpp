#include <crosswind/platform/application.hpp>


// USAGE:
//btRigidBody* tgtBody /* = ... */;
//YourContext foo;
//ContactSensorCallback callback(*tgtBody/*, foo*/);
//world->contactTest(tgtBody,callback);


class green_hill_zone: public cw::simulation::stage{
public:
    green_hill_zone(){

        this->name = "green_hill_zone";

    }

    virtual void init(std::shared_ptr<cw::platform::backend::interface::engine> engine){

        engine->mixer->load_music("green_hill", "green_hill_zone_bgm.ogg");
        engine->mixer->load_effect("jump", "Jump.wav");

        auto sonic_model  = engine->image->load_model(glm::vec3(0, 80, 0), glm::vec3( 40,  42, 10), "sonic.json");

        int chunk_size = 256;
        int offset = 0;
        for(int i = 0; i<4; i++){

            auto m = engine->image->load_model(glm::vec3(0 + offset, 0, 0), glm::vec3(chunk_size, chunk_size, 10), "ground.json");

            offset += 256;

            glm::vec3 ground_offset = m->get_origin();
            ground_offset.y = -96;

            auto r = engine->physics->create_rigid_body<cw::physics::box>(ground_offset,
                            glm::vec3(256, 64, 10),
                            0);

            r->set_linear_factor(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

            m->attach_rigid_body("ground_body", r, false);

            ground_models.push_back(m);
        }

        sonic_body =
                engine->physics->create_character(glm::vec3(0, 80, 0), glm::vec2(40, 42), 0.35);

      //  sonic_body->set_activation_policy(DISABLE_DEACTIVATION);
      //  sonic_body->set_linear_factor(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));


        sonic_model->attach_character("sonic_body", sonic_body, true);

        this->sonic_body->set_jump_speed(6.5f);


        post_event([this, engine, sonic_model](){

                if(this->sonic_body->on_ground()) {
                    if(this->sonic_body->get_speed().x > 0){
                        sonic_model->change_animation("walk");
                    } else if(this->sonic_body->get_speed().x < 0){
                        sonic_model->change_animation("walk");
                    } else {
                        sonic_model->change_animation("stand");
                    }

                    std::cout << "SPD X: " << this->sonic_body->get_speed().x << std::endl;
                }

        }, true);

        // jumping
        post_event([this, engine, sonic_model](){
            if(engine->input_listener->is_key_down("k")){

                if(this->sonic_body->on_ground()) {
                    this->sonic_body->jump();
                    sonic_model->change_animation("roll_1");
                    engine->mixer->play_effect("jump");

                }

            }

        }, true);


        // movement
        post_event([this, engine, sonic_model](){

            if(engine->input_listener->is_key_down("Right")){

                float acc = 0.046875;

                auto spd = this->sonic_body->get_speed();

                spd.x += acc;

                if(spd.x > 6){
                    spd.x = 6;
                }

                this->sonic_body->set_speed(spd);

                if(this->sonic_body->on_ground()){
                    if(spd.x >= 6){
                        sonic_model->change_animation("run");
                    } else {
                        sonic_model->change_animation("walk");
                    }
                }

            }

            if(engine->input_listener->is_key_down("Left")){

                float acc = -0.046875;

                auto spd = this->sonic_body->get_speed();

                spd.x += acc;

                if(spd.x < -6){
                    spd.x = -6;
                }

                this->sonic_body->set_speed(spd);

                if(this->sonic_body->on_ground()){
                    if(spd.x <= -6){
                        sonic_model->change_animation("run");
                    } else {
                        sonic_model->change_animation("walk");
                    }
                }

            }

        }, true);

        // friction
        post_event([this, engine, sonic_model](){

            if(!engine->input_listener->is_key_down("Left") && !engine->input_listener->is_key_down("Right")){

                auto spd = this->sonic_body->get_speed();

                if(spd.x > 0){

                    float frc = 0.046875f;

                    spd.x -= frc;

                    if(spd.x < 0.0f ){
                        spd.x = 0.0f;
                    }

                } else if(spd.x < 0) {
                    float frc = -0.046875f;

                    spd.x -= frc;

                    if(spd.x > 0.0f ){
                        spd.x = 0.0f;
                    }
                }

                this->sonic_body->set_speed(spd);

            }

        }, true);


        post_event([this](){

            auto c = this->camera_list["current"];

//            c->set_position(c->get_position() + glm::vec3(10.0f, 0.0f, 0.0f));

            c->set_position(this->sonic_body->get_origin());


        }, true);



        engine->physics->add_character(sonic_body);


        add("sonic",  sonic_model);

        for(int i = 0; i<ground_models.size(); i++){
            add("ground", ground_models[i]);

            for(auto mapping : ground_models[i]->get_rigid_bodies()){
                engine->physics->add_rigid_body(mapping.second);
            }
        }


    }

    virtual void update(double delta) override {

        for(auto& element: standard_queue){
            element->update(delta);
        }

//        ContactSensorCallback callback(sonic_body->physic_body.get());
 //       physics->contact_test(sonic_body, callback);

    }


    virtual void deinit(std::shared_ptr<cw::platform::backend::interface::engine> engine){
        engine->physics->remove_character(sonic_body);

        for(int i = 0; i<ground_models.size(); i++){

            for(auto mapping : ground_models[i]->get_rigid_bodies()){
                engine->physics->remove_rigid_body(mapping.second);
            }
        }
    }

private:
    std::shared_ptr<cw::physics::kinematic_character> sonic_body;
    std::vector<std::shared_ptr<cw::simulation::model> > ground_models;
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