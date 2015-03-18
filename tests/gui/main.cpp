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

            engine->image->load_texture("sonic_wait", "SonAni_Wait_intro.png");


            auto sonic_model  = engine->image->load_model(glm::vec3(0,0,0), glm::vec3(10,10,1), "sonic.json");

            add(sonic_model);
        }

        virtual void deinit(std::shared_ptr<cw::platform::backend::interface::engine> engine){

        }



    };

    app->add_stage(std::make_shared<green_hill_zone>());
    app->swap_stage("current", "green_hill_zone");
    app->run();


    return 0;
}