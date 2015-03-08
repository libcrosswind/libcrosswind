#pragma once

#include <string>

#include <glm/glm.hpp>


#include <crosswind/concurrent/atomic_property.hpp>
#include <crosswind/concurrent/mutex_property.hpp>
#include <crosswind/geometry/rectangle.hpp>
#include <crosswind/platform/sdl/sdl_core_system.hpp>
#include <crosswind/platform/sdl/sdl_audio_system.hpp>
#include <crosswind/platform/sdl/sdl_image_system.hpp>
#include <crosswind/platform/sdl/sdl_window.hpp>
#include <crosswind/platform/sdl/sdl_fps_limiter.hpp>
#include <crosswind/platform/sdl/sdl_input_listener.hpp>

#include <crosswind/simulation/stage.hpp>



namespace cw{
namespace platform{

        class application;

}// namespace platform
}// namespace cw

#include <iostream>

class cw::platform::application{
public:
    application(const std::string& title, const glm::vec4& bounds, int fps = 60):
    sdl_core_system (new sdl::sdl_core_system ( SDL_INIT_VIDEO | SDL_INIT_AUDIO    )),
    sdl_audio_system(new sdl::sdl_audio_system( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )), 
    sdl_image_system(new sdl::sdl_image_system( IMG_INIT_PNG                       )){

        sdl_window = std::make_shared<sdl::sdl_window>(title.c_str(), bounds, SDL_WINDOW_OPENGL);
        sdl_window->set_clear_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        sdl_fps_limiter = std::make_shared<sdl::sdl_fps_limiter>(fps);
        sdl_input_listener = std::make_shared<sdl::sdl_input_listener>();
    }



    virtual void run(){

        sdl_fps_limiter->reset_delta();
        running.set(true);
        int frame_counter = 0;

        while (running.get()) {

            frame_counter++;

            sdl_fps_limiter->begin();

            handle_application_events();
            handle_input();
            handle_update();
            handle_rendering();

            double fps = sdl_fps_limiter->end();

            if(frame_counter == 1000){
                frame_counter = 0;
                std::cout<< "FPS: " << fps << std::endl;
            }

        }

    }

    void add_stage(auto stage){
        stage->init(sdl_audio_system);
        stages(stage->name.get(), stage);
    }

    void swap_stage(const std::string& previous_stage, const std::string& new_stage){
        stages(previous_stage, stages(new_stage));
    }

private:
    void handle_application_events(){
        while(SDL_PollEvent(&event)){
            //User requests quit
            if(event.type == SDL_QUIT){
                running.set(false);
            }
        }

        stages("current")->handle_stage_events();
    }

    void handle_input(){

        sdl_input_listener->refresh();

        stages("current")->handle_input(sdl_input_listener);

    }

    void handle_update(){
        stages("current")->update(sdl_fps_limiter->get_delta());
    }

    void handle_rendering(){
        sdl_window->clear();
        stages("current")->render();
        sdl_window->present();
    }


private:
    std::shared_ptr< sdl::sdl_core_system  >  sdl_core_system;
    std::shared_ptr< sdl::sdl_image_system >  sdl_image_system;
    std::shared_ptr< sdl::sdl_audio_system >  sdl_audio_system;

    std::shared_ptr<sdl::sdl_fps_limiter>   sdl_fps_limiter;
    std::shared_ptr<sdl::sdl_window>        sdl_window;
    std::shared_ptr<sdl::sdl_input_listener> sdl_input_listener;


    SDL_Event event;

    concurrent::atomic_property<bool> running;

    concurrent::mutex_map<std::string, std::shared_ptr<simulation::stage> > stages;
};// class application
