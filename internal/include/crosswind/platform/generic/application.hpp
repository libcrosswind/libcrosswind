#pragma once

#include <string>

#include <crosswind/core/concurrent/mutexed_property.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_system.hpp>
#include <crosswind/platform/generic/detail/sdl/sdl_window.hpp>
#include <crosswind/standard/geometry/rectangle.hpp>

namespace cw{
namespace platform{
namespace generic{

    class application;

}// namespace generic
}// namespace platform
}// namespace cw

class cw::platform::generic::application{
public:
    application(): bounds(0, 0, 640, 480), title("Main window"), sdl_system(new detail::sdl::sdl_system(SDL_INIT_VIDEO)){
    }

    virtual void run(){
        auto& dim = bounds.size.acquire();

        window =
                std::shared_ptr<sdl_window>
                (new detail::sdl::sdl_window(title.get().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dim.x, dim.y, SDL_WINDOW_RESIZABLE));

        bounds.size.release();
        
/*        while (true) {
            window->refresh();
            window->wait(10);
        }
*/


//        on_exit();

    }

    standard::geometry::rectangle<int> bounds;
    core::concurrent::mutexed_property<std::string> title;
    std::shared_ptr<detail::sdl::sdl_window> window;
    std::shared_ptr<detail::sdl::sdl_system> sdl_system;

};// class application

