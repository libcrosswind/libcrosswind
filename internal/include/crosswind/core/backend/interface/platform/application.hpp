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
    application(const std::string& title,
                const glm::vec2 window_settings,
                const glm::vec2 default_resolution,
                const glm::vec2 window_resolution,
                const glm::vec3& world_scale,
                int fps = 60){

#if defined(USE_SDL2)

            std::vector<int> engine_settings = {
                    SDL_INIT_VIDEO | SDL_INIT_AUDIO,
                    IMG_INIT_PNG,
                    44100, MIX_DEFAULT_FORMAT, 2, 2048
            };

            auto graphical_settings = std::make_tuple(title, window_settings, window_resolution, fps, SDL_WINDOW_OPENGL);
            // default_resolution

            //We wil treat centimeters as pixels where 1 millimeter = 3.78 pixels

            std::vector<glm::vec3> physics_settings{
                    glm::vec3(0.0f, -10.0f, 0.0f),// gravity
                    glm::vec3(0.01f, 0.01f, 0.01f),// scale
                    glm::vec3(1.0f * world_scale[0], 1.0f * world_scale[1], 1.0f * world_scale[2])    // unit value
            };// 1 pixel represents 0.00026458 meters. We set this property to ensure correct graphical calculations.

            engine = std::make_shared<backend::sdl::engine>(engine_settings, graphical_settings, physics_settings);

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

            engine->physics->update(1/60.0);

            handle_update();
            handle_rendering();

            double fps = engine->window->fps_limiter->end();

        }

        stages["current"]->deinit(engine);
    }

    void add_stage(auto stage){
        stage->setup(engine);
        stage->init(engine);
        engine->physics->init_debug_drawer(stage->get_camera("main_camera"));
        stages[stage->name] = stage;
    }

    void swap_stage(const std::string& previous_stage, const std::string& new_stage){
        stages[previous_stage] = stages[new_stage];
    }

private:
    void handle_application_events(){
        while(SDL_PollEvent(&event)){
                //User requests quit
                if(event.type == SDL_QUIT){
                        engine->running = false;
                }
        }

        stages["current"]->handle_stage_events();
    }

    void handle_input(){

        engine->input_listener->update();

    }

    void handle_update(){
        stages["current"]->update(1/60.0/*engine->window->fps_limiter->get_delta()*/);
    }

    void handle_rendering(){
        engine->window->clear();
        stages["current"]->render();
      //  engine->physics->debug_draw_world();
        engine->window->present();
    }


private:
    std::shared_ptr<backend::interface::engine> engine;

    SDL_Event event;

    std::map<std::string, std::shared_ptr<simulation::stage> > stages;
};// class application
