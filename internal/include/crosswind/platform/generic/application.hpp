#pragma once

#include <string>

#include <crosswind/platform/generic/display_window.hpp>
#include <crosswind/core/concurrent/mutexed_property.hpp>

namespace cw{
namespace platform{
namespace generic{

    class application;

}// namespace generic
}// namespace platform
}// namespace cw

class cw::platform::generic::application{
public:
    application(){

        bounds.width  = 640;
        bounds.height = 480;
        title = std::string("Main window");
    }

    virtual void run(){

        window =
                std::shared_ptr<display_window>(new display_window(bounds.width, bounds.height, title));

        while (window->is_open() ) {
            window->refresh();
            window->wait(10);
        }

//        on_exit();

    }

    core::concurrent::mutexed_property<std::string> title;
    std::shared_ptr<display_window> window;
    standard::geometry::rectangle<int> bounds;

};// class application

