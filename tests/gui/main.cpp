#include <crosswind/core/javascript/json.hpp>

#include <crosswind/platform/generic/application.hpp>

int main(int argc, char **argv) {


    cw::platform::generic::filesystem::add_directory("assets", true);
    cw::platform::generic::filesystem::add_directory("tests/gui", true);

    {
        cw::core::javascript::json json;

        json.from_file("data.json");

        auto &raw_json = json.data.acquire();
        std::cout << raw_json << std::endl;

        json.data.release();
    }


    cw::platform::generic::application app;

    app.init();

    [&app](){
        class dummy_stage: public cw::standard::simulation::stage{
        public:
            dummy_stage(std::shared_ptr<cw::standard::simulation::sdl_renderer> renderer)
                    :cw::standard::simulation::stage(renderer){
                auto renderer_ptr = sdl_renderer->renderer.acquire();

                cw::standard::geometry::point<int> pos(10, 10);
                cw::standard::geometry::point<int> dim(50, 50);

                gui_elements.push_back
                        (std::shared_ptr<cw::standard::simulation::image_actor>
                                (new cw::standard::simulation::image_actor(pos, dim, "button.json", renderer_ptr)));
                sdl_renderer->renderer.release();
            }
        };

        app.stages("current", std::shared_ptr<cw::standard::simulation::stage>(new dummy_stage(app.sdl_renderer)));
    }();


    app.run();

    return 0;

}