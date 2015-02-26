#include <crosswind/core/javascript/json.hpp>

#include <crosswind/platform/generic/application.hpp>

int main(int argc, char **argv) {
    cw::platform::generic::filesystem::add_directory("assets", true);

    cw::platform::generic::application app;

    app.init();

    class dummy_stage: public cw::standard::simulation::stage{
    public:
        dummy_stage(std::shared_ptr<cw::standard::simulation::sdl_renderer> renderer)
                :cw::standard::simulation::stage(renderer){
            auto renderer_ptr = sdl_renderer->renderer.acquire();

            cw::standard::geometry::point<int> pos(10, 10);
            cw::standard::geometry::point<int> dim(150, 40);

            gui_elements.push_back
                    (std::shared_ptr<cw::standard::simulation::image_actor>
                            (new cw::standard::simulation::image_actor(pos, dim, "sprite_blue_button.json", renderer_ptr)));

            pos.x = 180;
            pos.y = 180;

            dim.x = 76;
            dim.y = 80;

            gui_elements.push_back
                    (std::shared_ptr<cw::standard::simulation::image_actor>
                            (new cw::standard::simulation::image_actor(pos, dim, "sonic.json", renderer_ptr)));


            sdl_renderer->renderer.release();
        }
    };

    app.stages("current", std::shared_ptr<cw::standard::simulation::stage>(new dummy_stage(app.sdl_renderer)));

    app.run();

    return 0;

}