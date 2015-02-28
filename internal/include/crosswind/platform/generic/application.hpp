#pragma once

#include <string>
#include <chrono>

#include <crosswind/core/concurrent/atomical_property.hpp>
#include <crosswind/core/concurrent/mutexed_property.hpp>
#include <crosswind/platform/generic/filesystem.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_system.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_image_system.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_window.hpp>
#include <crosswind/standard/geometry/rectangle.hpp>
#include <crosswind/standard/simulation/sdl_renderer.hpp>
#include <crosswind/standard/simulation/stage.hpp>



namespace cw{
namespace platform{
namespace generic{

    class application;

}// namespace generic
}// namespace platform
}// namespace cw

class cw::platform::generic::application{
public:
    application(): 
    bounds(0, 0, 640, 480), 
    title("Main window"), 
    sdl_system(new detail::sdl::sdl_system(SDL_INIT_VIDEO)),
    sdl_image_system(new detail::sdl::sdl_image_system(IMG_INIT_PNG)){


    }

    virtual void init(){

        auto& dim = bounds.size.acquire();

        display_window = std::shared_ptr<detail::sdl::sdl_window>(new detail::sdl::sdl_window(title.get().c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                dim.x, dim.y,
                SDL_WINDOW_RESIZABLE));

        bounds.size.release();

        auto window_ptr = display_window->window.acquire();
        sdl_renderer = std::shared_ptr<standard::simulation::sdl_renderer>
                (new standard::simulation::sdl_renderer(window_ptr, -1, SDL_RENDERER_ACCELERATED));
        display_window->window.release();

    }

    virtual void run(){

        const int SCREEN_FPS = 60;
        const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

        int frame_counter = 0;

        running.set(true);
        previous_delta_time = std::chrono::high_resolution_clock::now();

        std::cout << running.get() <<std::endl;
        while (running.get()) {

            auto begin = std::chrono::high_resolution_clock::now();

            handle_application_events();
            handle_input_events();
            handle_update();
            handle_rendering();

            auto end = std::chrono::high_resolution_clock::now();
            auto time_diference = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
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
//        on_exit();
    }

    void handle_application_events(){
/*        events.iterator([](auto& element){
            if(element.first.first == "stage-swap"){
                element.first.second
            }
        });*/
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

        sdl_renderer->set_draw_color(0, 0, 0);
        sdl_renderer->clear();

        stages("current")->render();

        sdl_renderer->present();
    }

    core::concurrent::mutexed_map<std::string, std::shared_ptr<standard::simulation::stage> > stages;
    std::shared_ptr<standard::simulation::sdl_renderer> sdl_renderer;

private:
    double get_delta() {

        auto current_time = std::chrono::high_resolution_clock::now();
        auto time_diference = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - previous_delta_time);
        double delta = time_diference.count();

        delta /= 1000000000;
        previous_delta_time = current_time;

        return delta;
    }

    std::chrono::high_resolution_clock::time_point previous_delta_time;

    standard::geometry::rectangle<int> bounds;
    core::concurrent::mutexed_property<std::string> title;
    core::concurrent::atomical_property<bool> running;

    std::shared_ptr<detail::sdl::sdl_window> display_window;
    std::shared_ptr<detail::sdl::sdl_system> sdl_system;
    std::shared_ptr<detail::sdl::sdl_image_system> sdl_image_system;
    SDL_Event event;

//    core::concurrent::mutexed_map<std::pair<std::string, std::string>, > events;

};// class application
