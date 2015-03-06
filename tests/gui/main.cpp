
#include <crosswind/platform/application.hpp>
#include <crosswind/platform/filesystem.hpp>

#include <crosswind/simulation/sprite.hpp>

int main(int argc, char **argv) {
    cw::platform::filesystem::add_directory("assets", true);

    auto app = std::make_shared<cw::platform::application>();
    app->init({SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480});

    class marble_zone: public cw::simulation::stage{
    public:
        marble_zone(){

            this->name.set("marble_zone");



/*
            btn_stand = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            btn_walk  = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            btn_run   = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            btn_play_audio = std::make_shared<cw::simulation::interactive_image>(pos, dim);
            sonic = std::make_shared<cw::simulation::standard_image>(pos, dim);

            add(btn_stand);
            add(btn_walk);
            add(btn_run);
            add(btn_play_audio);
            add(sonic);*/

            simple_sprite = std::make_shared<cw::simulation::sprite>(cw::math::vector3(-0.5f, -0.5f, 1.0f),
                    cw::math::vector3(1.0f,1.0f,0.0f));
            add(simple_sprite);
        }

        virtual void init(std::shared_ptr<cw::platform::sdl::sdl_gl_renderer> sdl_gl_renderer,
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
/*        std::shared_ptr<cw::simulation::interactive_image> btn_stand;
        std::shared_ptr<cw::simulation::interactive_image> btn_walk;
        std::shared_ptr<cw::simulation::interactive_image> btn_run;
        std::shared_ptr<cw::simulation::interactive_image> btn_play_audio;

        std::shared_ptr<cw::simulation::standard_image> sonic;*/

        std::shared_ptr<cw::simulation::sprite> simple_sprite;
    };

    app->add_stage(std::make_shared<marble_zone>());
    app->swap_stage("current", "marble_zone");
    app->run();

    return 0;



}