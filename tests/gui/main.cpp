
#include <crosswind/platform/application.hpp>
#include <crosswind/platform/filesystem.hpp>

#include <crosswind/simulation/interactive_image.hpp>

int main(int argc, char **argv) {
    cw::platform::filesystem::add_directory("assets", true);

    cw::platform::application app;

    app.init();

    class dummy_stage: public cw::simulation::stage{
    public:
        dummy_stage(std::shared_ptr<cw::platform::sdl::sdl_renderer> renderer):
                cw::simulation::stage(renderer){


            cw::geometry::point<int> pos(10, 10);
            cw::geometry::point<int> dim(150, 40);

            add(std::shared_ptr<cw::simulation::interactive_image>
                    (new cw::simulation::interactive_image(pos, dim, sdl_renderer, "sprite_blue_button.json")));

            pos.x = 180;
            pos.y = 180;

            dim.x = 76;
            dim.y = 80;

  /*          gui_elements.push_back
                    (std::shared_ptr<cw::simulation::standard_image>
                            (new cw::simulation::standard_actor(pos, dim, "sonic.json", renderer_ptr)));
*/
        }
    };

    app.stages("current", std::shared_ptr<cw::simulation::stage>(new dummy_stage(app.sdl_renderer)));

    app.run();

    return 0;

}