
#include <crosswind/platform/application.hpp>
#include <crosswind/platform/filesystem.hpp>

#include <crosswind/simulation/interactive_image.hpp>

int main(int argc, char **argv) {
    cw::platform::filesystem::add_directory("assets", true);


    auto app = std::make_shared<cw::platform::application>();
    app->init();

    class dummy_stage: public cw::simulation::stage{
    public:
        dummy_stage(std::shared_ptr<cw::platform::sdl::sdl_renderer> sdl_renderer){

            cw::geometry::point<int> pos(10, 10);
            cw::geometry::point<int> dim(150, 40);

            btn_stand = std::make_shared<cw::simulation::interactive_image>(pos, dim, sdl_renderer, "blue_button.json");
            pos.x += dim.x + 10;
            btn_walk  = std::make_shared<cw::simulation::interactive_image>(pos, dim, sdl_renderer, "blue_button.json");
            pos.x += dim.x + 10;
            btn_run   = std::make_shared<cw::simulation::interactive_image>(pos, dim, sdl_renderer, "blue_button.json");

            add(btn_stand);
            add(btn_walk);
            add(btn_run);


            pos.x = 180;
            pos.y = 150;

            dim.x = 76;
            dim.y = 80;

            sonic = std::make_shared<cw::simulation::standard_image>(pos, dim, sdl_renderer, "sonic.json");

            btn_stand->on_mouse_down += [this](){
                this->sonic->swap_graphical_item(this->sonic->animations, "current", "stand");
            };

            btn_walk->on_mouse_down += [this](){
                this->sonic->swap_graphical_item(this->sonic->animations, "current", "walk");
            };

            btn_run->on_mouse_down += [this](){
                this->sonic->swap_graphical_item(this->sonic->animations, "current", "run");
            };

            add(sonic);

        }

    private:
        std::shared_ptr<cw::simulation::interactive_image> btn_stand;
        std::shared_ptr<cw::simulation::interactive_image> btn_walk;
        std::shared_ptr<cw::simulation::interactive_image> btn_run;
        std::shared_ptr<cw::simulation::standard_image> sonic;
    };

    app->stages("current", std::make_shared<dummy_stage>(app->sdl_renderer));

    app->run();

    return 0;

}