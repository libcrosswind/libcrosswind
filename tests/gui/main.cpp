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
        engine->mixer->play_music("green_hill");

        engine->mixer->load_effect("jump", "Jump.wav");
        engine->mixer->load_effect("stop", "Skid.wav");
        engine->mixer->load_effect("spin", "Spin.wav");

        auto sonic_model  = engine->image->load_model(glm::vec3(0, 80, 0), glm::vec3( 40,  42, 10), "sonic.json");

        int chunk_size = 256;
        int offset = 0;
        for(int i = 0; i<10; i++){

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

        this->sonic_body =
                engine->physics->create_character(glm::vec3(0, 80, 0), glm::vec2(26, 24), 0.35);

      //  sonic_body->set_activation_policy(DISABLE_DEACTIVATION);
      //  sonic_body->set_linear_factor(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));


        sonic_model->attach_character("sonic_body", sonic_body, true);

        this->sonic_body->set_jump_speed(6.5f + (224.0f / 480.0f * 6.5f));

        sonic_model->set_facing(true);
        sonic_model->conditions["moving"]  = false;
        sonic_model->conditions["braking"]  = false;
        sonic_model->conditions["rolling"] = false;
        sonic_model->conditions["jumping"]  = false;

        // ground animations
        post_event([this, engine, sonic_model](){

                if(this->sonic_body->on_ground()) {

                    if(this->sonic_body->get_speed().x > 0){
                        sonic_model->set_facing(true);
                    } else if(this->sonic_body->get_speed().x < 0){
                        sonic_model->set_facing(false);
                    }

                    if(engine->input_listener->is_key_down("Up")) {

                        if(this->sonic_body->get_speed().x == 0.0f){
                            sonic_model->change_animation("look_up", sonic_model->get_facing());
                        }

                    } else if(engine->input_listener->is_key_down("Down")){

                        if(glm::abs(this->sonic_body->get_speed().x) >=  0.53125f){

                            if(!sonic_model->conditions["rolling"]){
                                sonic_model->change_animation("roll_1", sonic_model->get_facing());
                                engine->mixer->play_effect("spin");
                                sonic_model->conditions["rolling"] = true;
                            }

                        } else if(this->sonic_body->get_speed().x == 0){
                            sonic_model->change_animation("duck", sonic_model->get_facing());
                        }


                    } else if(engine->input_listener->is_key_down("Left") != engine->input_listener->is_key_down("Right")){

                        if(glm::abs(this->sonic_body->get_speed().x) >= 6.0f){
                            if(!sonic_model->conditions["rolling"] &&
                                    !sonic_model->conditions["braking"]){

                                sonic_model->change_animation("run", sonic_model->get_facing());
                            }

                        } else {
                            if(!sonic_model->conditions["rolling"] &&
                                    !sonic_model->conditions["braking"]){

                                sonic_model->change_animation("walk", sonic_model->get_facing());

                            }
                        }

                        if(glm::abs(this->sonic_body->get_speed().x) >= 4.5f){
                            bool should_brake = false;

                            if(sonic_model->get_facing() && engine->input_listener->is_key_down("Left")){
                                should_brake = true;
                            } else if(!sonic_model->get_facing() && engine->input_listener->is_key_down("Right")){
                                should_brake = true;
                            }

                            if(should_brake && !sonic_model->conditions["braking"] && !sonic_model->conditions["rolling"]){
                                sonic_model->change_animation("stop", sonic_model->get_facing());
                                engine->mixer->play_effect("stop");
                                sonic_model->conditions["braking"] = true;
                            }
                        }


                        if(sonic_model->conditions["braking"]){

                            if(engine->input_listener->is_key_down("Left") && this->sonic_body->get_speed().x <= 0.0f){
                                sonic_model->conditions["braking"] = false;
                            } else if(engine->input_listener->is_key_down("Right") && this->sonic_body->get_speed().x >= 0.0f){
                                sonic_model->conditions["braking"] = false;
                            }
                        }


                        if(sonic_model->conditions["rolling"]){

                            if(sonic_model->get_facing() && this->sonic_body->get_speed().x <= 0.0f){
                                sonic_model->conditions["rolling"] = false;
                            } else if(!sonic_model->get_facing() && this->sonic_body->get_speed().x >= 0.0f){
                                sonic_model->conditions["rolling"] = false;
                            }
                        }


                    } else{

                        if(this->sonic_body->get_speed().x == 0) {
                            sonic_model->conditions["rolling"] = false;
                            sonic_model->conditions["braking"] = false;
                            sonic_model->change_animation("stand", sonic_model->get_facing());
                        }

                    }


                    float frame_duration = glm::max(8.0f - glm::abs(this->sonic_body->get_speed().x), 3.0f);

                    frame_duration *= 1.0f / 60.0f; // 1 second / 60 frames;

                    sonic_model->get_animations()["walk"]->duration =
                            frame_duration * sonic_model->get_animations()["walk"]->frames.size();

                    sonic_model->get_animations()["run"]->duration =
                            frame_duration * sonic_model->get_animations()["run"]->frames.size();


                    frame_duration = glm::max(8.0f - glm::abs(this->sonic_body->get_speed().x), 1.0f);

                    frame_duration *= 1.0f / 60.0f;

                    sonic_model->get_animations()["roll_1"]->duration =
                            frame_duration * sonic_model->get_animations()["roll_1"]->frames.size();

                }

        }, true);

        // jumping
        post_event([this, engine, sonic_model](){

            if(engine->input_listener->is_key_down("k")){

                if(this->sonic_body->on_ground()) {
                    this->sonic_body->jump();
                    sonic_model->conditions["rolling"] = false;
                    sonic_model->change_animation("roll_1", sonic_model->get_facing());
                    engine->mixer->play_effect("jump");
                }

            }

        }, true);

        // movement
        post_event([this, engine, sonic_model](){

            if(engine->input_listener->is_key_down("Right") != engine->input_listener->is_key_down("Left")){

                float acc = 0.046875;
                float dec = 0.5f;

                auto spd = this->sonic_body->get_speed();

                if(engine->input_listener->is_key_down("Left")){
                    acc *= -1.0f;
                    dec *= -1.0f;
                }

                if(sonic_model->conditions["braking"]){
                    spd.x += dec;
                } else if(sonic_model->conditions["rolling"]){

                    if(glm::abs(spd.x) > 16.0f){
                        spd.x = 16.0f * glm::sign(spd.x);
                    }

                } else {

                    spd.x += acc;

                    if(glm::abs(spd.x) > 6.0f){
                        spd.x = 6.0f * glm::sign(spd.x);
                    }

                }

                this->sonic_body->set_speed(spd);

            }

        }, true);

        // friction calculation
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


        post_event([this, engine](){

            auto c = this->camera_list["current"];
            c->set_position(this->sonic_body->get_origin());



        }, true);



        engine->physics->add_character(sonic_body);


        add("sonic",  sonic_model);

        for(int i = 0; i<ground_models.size(); i++){
            add("ground_" + std::to_string(i), ground_models[i]);

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