#pragma once

#include <string>
#include <chrono>

#include <crosswind/core/concurrent/mutexed_property.hpp>
#include <crosswind/platform/generic/filesystem.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_system.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_image_system.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_window.hpp>
#include <crosswind/standard/geometry/rectangle.hpp>
#include <crosswind/standard/simulation/sdl_renderer.hpp>

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

    virtual void run(){
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

        auto renderer_ptr = sdl_renderer->renderer.acquire();
        standard::drawing::sdl_texture sprite1(renderer_ptr, 
                                            cw::platform::generic::filesystem::get_file_path("background-blue.png").c_str());
        sdl_renderer->renderer.release();
 
        bool running = true;

        while (running) {
                    // Process input
            SDL_Event event;
            while (SDL_PollEvent(&event))
                if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)))
                    running = false;

            // Clear screen
            sdl_renderer->set_draw_color(128, 32, 200);
            sdl_renderer->clear();

            sdl_renderer->copy(sprite1);

            sdl_renderer->present();

            // Frame limiter
            SDL_Delay(1);
        }

//        on_exit();

    }

private:
    double get_delta() {

        auto current_time = std::chrono::high_resolution_clock::now();
        auto time_diference = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - previous_time);
        double delta = time_diference.count();

        delta /= 1000000000;
        previous_time = current_time;

        return delta;
    }


    std::chrono::high_resolution_clock::time_point previous_time;

    standard::geometry::rectangle<int> bounds;
    core::concurrent::mutexed_property<std::string> title;
    std::shared_ptr<detail::sdl::sdl_window> display_window;
    std::shared_ptr<detail::sdl::sdl_system> sdl_system;
    std::shared_ptr<detail::sdl::sdl_image_system> sdl_image_system;

    std::shared_ptr<standard::simulation::sdl_renderer> sdl_renderer;
};// class application

