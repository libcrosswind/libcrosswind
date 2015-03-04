
#include <crosswind/platform/application.hpp>
#include <crosswind/platform/filesystem.hpp>

#include <crosswind/simulation/interactive_image.hpp>

int main(int argc, char **argv) {
    cw::platform::filesystem::add_directory("assets", true);

    auto app = std::make_shared<cw::platform::application>();
    app->init();

    class marble_zone: public cw::simulation::stage{
    public:
        marble_zone(){

            this->name.set("marble_zone");
/*
            cw::geometry::point<int> pos(10, 10);
            cw::geometry::point<int> dim(100, 40);


            btn_stand = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            pos.x += dim.x + 10;
            btn_walk  = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            pos.x += dim.x + 10;
            btn_run   = std::make_shared<cw::simulation::interactive_image>(pos, dim);

            pos.x += dim.x + 10;
            btn_play_audio = std::make_shared<cw::simulation::interactive_image>(pos, dim);

            pos.x = 180;
            pos.y = 150;

            dim.x = 76;
            dim.y = 80;

            sonic = std::make_shared<cw::simulation::standard_image>(pos, dim);

            add(btn_stand);
            add(btn_walk);
            add(btn_run);
            add(btn_play_audio);
            add(sonic);*/
        }

        virtual void init(std::shared_ptr<cw::platform::sdl::sdl_renderer> sdl_renderer,
                std::shared_ptr<cw::platform::sdl::sdl_audio_system> sdl_audio_system){

            //sdl_audio_system->load_music("marble", cw::platform::filesystem::get_file_path("marble_zone_bgm.ogg"));

/*            btn_stand->init(sdl_renderer, "blue_button.json");
            btn_walk->init(sdl_renderer, "blue_button.json");
            btn_run->init(sdl_renderer, "blue_button.json");
            btn_play_audio->init(sdl_renderer, "blue_button.json");
            sonic->init(sdl_renderer, "sonic.json");

            btn_stand->on_mouse_down += [this](){
                post_event([this](){
                    this->sonic->swap_graphical_item(this->sonic->animations, "current", "stand");
                });
            };

            btn_walk->on_mouse_down += [this](){
                post_event([this](){
                    this->sonic->swap_graphical_item(this->sonic->animations, "current", "walk");
                });
            };

            btn_run->on_mouse_down += [this](){
                post_event([this](){
                    this->sonic->swap_graphical_item(this->sonic->animations, "current", "run");
                });
            };

            btn_play_audio->on_mouse_down += [this, sdl_audio_system](){
                this->post_event([sdl_audio_system](){
                    sdl_audio_system->play_music("marble");
                });
            };*/
        }

    private:
        std::shared_ptr<cw::simulation::interactive_image> btn_stand;
        std::shared_ptr<cw::simulation::interactive_image> btn_walk;
        std::shared_ptr<cw::simulation::interactive_image> btn_run;
        std::shared_ptr<cw::simulation::interactive_image> btn_play_audio;

        std::shared_ptr<cw::simulation::standard_image> sonic;
    };

    app->add_stage(std::make_shared<marble_zone>());
    app->swap_stage("current", "marble_zone");
    app->run();

    return 0;



}