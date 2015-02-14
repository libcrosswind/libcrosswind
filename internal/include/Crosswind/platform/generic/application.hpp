#pragma once

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
    application(){
        buffering = false;
        buffer_key = 0;
        buffer_counter = 0.0;
        buffer_frames = 1;
    }

    void render(std::shared_ptr<texture> render_texture) override {

        render_texture->clear();

        for(auto& element : elements){
            element->render(render_texture);
        }

        render_texture->render_to_display(display_window);

    }

    virtual void run(){

        display_window =
                std::shared_ptr<display_target>(new display_target(get_absolute_width(), get_absolute_height(), get_text()));

        render_texture = (new texture(get_width(), get_height(), get_depth(), 4));

        while (display_window->is_open() ) {

            double delta = get_delta();

            handle_input(delta);

            for(auto& element : elements){
                element->update(delta);
            }

            update();

            render();

            display_window->wait(10);
        }

        on_exit();

    }

    double get_delta() {
        // Gett current time as a std::chrono::time_point
        // which basically contains info about the current point in time
        auto current_time = std::chrono::high_resolution_clock::now();

        // Compare the two to create time_point containing delta time in nanosecnds
        auto time_diference = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - previous_time);

        // Get the tics as a variable
        double delta = time_diference.count();

        // Turn nanoseconds into seconds
        delta /= 1000000000;

        previous_time = current_time;
        return delta;
    }

    void handle_input(double delta) {

        //TODO implement z-order.
        // button clicked. //TODO reduce iterations and implement Z-order.
        for (auto &element:elements) {
            if (window->get_mouse_button()) {
                //Send mouse down event to all elements;
                element->on_mouse_down( window->get_mouse_x(),
                        window->get_mouse_y(),
                        window->get_mouse_button());
            } else {
                //Send mouse released event to all elements.
                element->on_mouse_up(window->get_mouse_x(), window->get_mouse_y());
            }

        }

        if (window->get_mouse_x() || window->get_mouse_y()) { // mouse moved
            for (auto &element : elements) {
                element->on_mouse_move(window->get_mouse_x(), window->get_mouse_y());
            }
        }

        if (window->get_keyboard_down()) {  // key down //@TODO single reads for atomics.

            if(window->get_keyboard_down() != get_buffer_key()){
                if(!get_buffering()){  //@TODO implement buffering for keypress

                    for (auto &element : elements) {
                        element->on_key_down(window->get_keyboard_down());
                    }

                    set_buffer_counter(0.0f);
                    set_buffering(true);
                    set_buffer_key(window->get_keyboard_down());
                }

            } else {

                if(get_buffering()){
                    set_buffer_counter(get_buffer_counter() + delta) ;

                    if(get_buffer_counter() >= (1.0f/ get_buffer_frames())){
                        set_buffer_counter(0.0f);
                        set_buffering(false);
                    }

                } else {
                    for (auto &element : elements) {
                        element->on_key_down(window->get_keyboard_down());
                    }
                }
            }


        } else {
            set_buffer_key(0);
        }

        if (window->get_keyboard_up()) { // key up
            set_buffer_counter(0.0f);
            set_buffering(false);
            set_buffer_key(0);

            for (auto &element : elements) {
                element->on_key_up(window->get_keyboard_up());
            }
        }
    }

    display_window window;
    standard::drawing::texture render_texture;

    std::chrono::high_resolution_clock::time_point previous_time;
    core::concurrent::atomical_property<bool> buffering;
    core::concurrent::atomical_property<int> buffer_key;
    core::concurrent::atomical_property<float> buffer_counter;
    core::concurrent::atomical_property<float> buffer_frames;

};// class application

