#pragma once

#include <string>
#include <chrono>

#include <crosswind/concurrent/atomic_property.hpp>
#include <crosswind/concurrent/mutex_property.hpp>

#include <crosswind/geometry/rectangle.hpp>

#include <crosswind/platform/sdl/sdl_core_system.hpp>
#include <crosswind/platform/sdl/sdl_audio_system.hpp>
#include <crosswind/platform/sdl/sdl_image_system.hpp>
#include <crosswind/platform/sdl/sdl_gl_renderer.hpp>
#include <crosswind/platform/sdl/sdl_window.hpp>

#include <crosswind/simulation/stage.hpp>



namespace cw{
namespace platform{

    class application;

}// namespace platform
}// namespace cw



class cw::platform::application{
public:
    application(): 
    bounds(new geometry::rectangle<int>(0, 0, 640, 480)),
    title("Main window"),
    sdl_core_system (new sdl::sdl_core_system ( SDL_INIT_VIDEO | SDL_INIT_AUDIO    )),
    sdl_audio_system(new sdl::sdl_audio_system( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )), 
    sdl_image_system(new sdl::sdl_image_system( IMG_INIT_PNG                       )){


    }


    virtual void init(){

        auto& dim = bounds->size.acquire();

        display_window = std::shared_ptr<sdl::sdl_window>(new sdl::sdl_window(title.get().c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                dim.x, dim.y,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN));

        bounds->size.release();

        auto window_ptr = display_window->window.acquire();

        std::vector<int> gl_version = {2, 1};
        sdl_gl_renderer = std::make_shared<sdl::sdl_gl_renderer>(gl_version, window_ptr);

        sdl_gl_renderer->set_draw_color(0.f, 0.f, 0.f);

        display_window->window.release();

        sdl_gl_renderer->set_perspective(45.0, 640.0/480.0, 1.0, 500.0);
    }

    virtual void run(){

        const int SCREEN_FPS = 60;
        const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

        running.set(true);
        previous_delta_time = std::chrono::high_resolution_clock::now();

        while (running.get()) {

            auto begin_frame = std::chrono::high_resolution_clock::now();
            
            handle_application_events();
            handle_input_events();
            handle_update();
            handle_rendering();

            auto end_frame = std::chrono::high_resolution_clock::now();
            auto time_diference = std::chrono::duration_cast<std::chrono::nanoseconds>(end_frame - begin_frame);
            double delta = time_diference.count();

            delta /= 1000000000;

            //If frame finished early
            int frameTicks = delta;
            if( frameTicks < SCREEN_TICKS_PER_FRAME )
            {
                //Wait remaining time
                SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
            }
        }
    }

    void handle_application_events(){
        stages("current")->handle_stage_events();
    }

    void handle_input_events(){
        while(SDL_PollEvent(&event)){
            //User requests quit
            if(event.type == SDL_QUIT){
                running.set(false);
            }

            stages("current")->handle_input(&event);

        }
    }

    void handle_update(){
        stages("current")->update(get_delta());
    }

    void handle_rendering(){

        sdl_gl_renderer->clear();
        sdl_gl_renderer->load_identity();

        stages("current")->render(sdl_gl_renderer);

        auto window_ptr = display_window->window.acquire();
        sdl_gl_renderer->present(window_ptr);
        display_window->window.release();
    }

    void add_stage(auto stage){
        stage->init(sdl_gl_renderer, sdl_audio_system);
        stages(stage->name.get(), stage);
    }

    void swap_stage(const std::string& previous_stage, const std::string& new_stage){
        stages(previous_stage, stages(new_stage));
    }

private:
    double get_delta() {

        auto current_time = std::chrono::high_resolution_clock::now();
        auto time_diference = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - previous_delta_time);
        double delta = time_diference.count();

        delta /= 1000000000;
        previous_delta_time = current_time;

        return delta;
    }

private:
    std::shared_ptr< sdl::sdl_core_system  >  sdl_core_system;
    std::shared_ptr< sdl::sdl_image_system >  sdl_image_system;
    std::shared_ptr< sdl::sdl_gl_renderer  >  sdl_gl_renderer;
    std::shared_ptr< sdl::sdl_audio_system >  sdl_audio_system;

    std::shared_ptr< sdl::sdl_window >  display_window;

    SDL_Event event;

    std::shared_ptr<geometry::rectangle<int> > bounds;
    concurrent::mutex_property<std::string> title;
    concurrent::atomic_property<bool> running;

    std::chrono::high_resolution_clock::time_point previous_delta_time;

    concurrent::mutex_map<std::string, std::shared_ptr<simulation::stage> > stages;


};// class application
