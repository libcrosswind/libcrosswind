#pragma once

#include <map>
#include <string>

#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>

#include <crosswind/platform/backend/sdl/engine.hpp>
#include <crosswind/simulation/stage.hpp>


namespace cw{
namespace platform{

        class application;

}// namespace platform
}// namespace cw


class cw::platform::application{
#define USE_SDL2 1
    
public:
    application(const std::string& title, const glm::vec4& bounds, int fps = 60){

#if defined(USE_SDL2)

        std::vector<int> engine_settings = {
                SDL_INIT_VIDEO | SDL_INIT_AUDIO,
                IMG_INIT_PNG,
                44100, MIX_DEFAULT_FORMAT, 2, 2048

        };


        auto window_settings = std::make_tuple(title, bounds, fps, SDL_WINDOW_OPENGL);


        std::vector<glm::vec3> physics_settings{
                glm::vec3(0.0f, -10.0f, 0.0f),                      // gravity
                glm::vec3(0.01, 0.01f, 0.01f),                      // scale
                glm::vec3(0.00026458f, 0.00026458f, 0.00026458f)    // unit value
        };// 1 pixel represents 0.00026458 meters. We set this property to ensure correct graphical calculations.

        engine = std::make_shared<backend::sdl::engine>(engine_settings, window_settings, physics_settings);

#else

#endif

}

#undef USE_SDL2

        virtual void run(){

                engine->window->fps_limiter->reset_delta();

                engine->running = true;


                while (engine->running) {


                        engine->window->fps_limiter->begin();

                        handle_application_events();
                        handle_input();

                        engine->physics_world->update(1/60.0);

                        handle_update();
                        handle_rendering();

                        double fps = engine->window->fps_limiter->end();

                }

          //      stages("current")->deinit(engine);

        }

        void add_stage(auto stage){
                stage->init(engine);
    //            stages(stage->name.get(), stage);
        }

        void swap_stage(const std::string& previous_stage, const std::string& new_stage){
//                stages(previous_stage, stages(new_stage));
        }

private:
        void handle_application_events(){
                while(SDL_PollEvent(&event)){
                //User requests quit
                        if(event.type == SDL_QUIT){
                                engine->running = false;
                }
        }

   //     stages("current")->handle_stage_events();
        }

        void handle_input(){

        engine->input_listener->update();

    //    stages("current")->handle_input(engine->input_listener);

        }

        void handle_update(){
     //   stages("current")->update(engine->window->fps_limiter->get_delta());
        }

        void handle_rendering(){
                engine->window->clear();
           //     stages("current")->render();
                engine->physics_world->debug_draw_world();
                engine->window->present();
        }


private:
    std::shared_ptr<backend::interface::engine> engine;

    SDL_Event event;

    std::map<std::string, std::shared_ptr<simulation::stage> > stages;
};// class application
