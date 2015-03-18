#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <crosswind/platform/application.hpp>


int main(int argc, char **argv) {

    cw::platform::filesystem::add_directory("assets", true);

    auto window_bounds = glm::vec4(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    auto app = std::make_shared<cw::platform::application>("Main Window", window_bounds);


    class green_hill_zone: public cw::simulation::stage{
    public:
        green_hill_zone(){

            this->name = "green_hill_zone";

        }

        virtual void init(std::shared_ptr<cw::platform::backend::interface::engine> engine){

            engine->mixer->load_music("green_hill", "green_hill_zone_bgm.ogg");

            auto sonic_model  = engine->image->load_model(glm::vec3(0, 80, 0), glm::vec3( 40,  42, 10), "sonic.json");
            auto ground_model = engine->image->load_model(glm::vec3(0,  0, 0), glm::vec3(256, 256, 10), "ground.json");

            box = engine->physics_world->create_rigid_body<cw::physics::box>(glm::vec3(0, 80, 0), glm::vec3(40, 42, 10), 0);

            engine->physics_world->add_rigid_body(box);

            add("sonic",  sonic_model);
            add("ground", ground_model);

        }

        virtual void deinit(std::shared_ptr<cw::platform::backend::interface::engine> engine){
            engine->physics_world->remove_rigid_body(box);
        }

    private:
        std::shared_ptr<cw::physics::box> box;
    };

    app->add_stage(std::make_shared<green_hill_zone>());
    app->swap_stage("current", "green_hill_zone");
    app->run();


    return 0;
}