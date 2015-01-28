#pragma once


#include <functional>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>

#include <Crosswind/gui/widgets/detail/grid.hpp>
#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/gui/widgets/detail/gui_element.hpp>
#include <Crosswind/gui/widgets/detail/display_target.hpp>



namespace cw{

    class window: public grid, public widget, public gui_element {

        public:
            enum window_flags{
                MULTITHREADED = 1 << 0
            };

            window(): is_multithreaded(false){

            }

            void init(std::shared_ptr<init_flags> flags = nullptr) override {
                //setup_flags = flags;

                if(flags){
                    flags->has(window_flags::MULTITHREADED)? is_multithreaded = true: is_multithreaded = false;
                }

                switch_texture("render", std::shared_ptr<texture>(new texture(get_width(), get_height(), get_depth(), 4)));

            }

            void show() override {
                set_visible(true);
                display_window =
                        std::shared_ptr<display_target>(new display_target(get_width(), get_height(), get_text()));

                on_show();

                if(is_multithreaded){
                    window_thread = std::thread(&widget::loop, this);
                } else {
                    loop();
                }

            }

            void hide() override {
                set_visible(false);
                on_hide();
            }

            void update(double delta) override {

                /*     frame_counter += delta;

                     if (frameCounter >= (max_fps)) {
                         frameCounter = 0.f;
                     }
                 */

            }


        void render(std::shared_ptr<texture> render_texture) override {

                render_texture->clear();

                for(auto& element : elements){
                    element->render(render_texture);
                }

                render_texture->render_to_display(display_window);

            }

            void loop() override {

                while (get_visible() && display_window->is_open() ) {

                    handle_input();

                    update(get_delta());

                    render(get_texture("render"));

                    display_window->wait(40);

                }
            }


        private:
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

            void handle_input() {

                //TODO implement z-order.
                // button clicked. //TODO reduce iterations and implement Z-order.
                for (auto &element:elements) {
                        if (display_window->get_mouse_button()) {
                            //Send mouse down event to all elements;
                            element->on_mouse_down( display_window->get_mouse_x(),
                                                    display_window->get_mouse_y(),
                                                    display_window->get_mouse_button());
                        } else {
                            //Send mouse released event to all elements.
                            element->on_mouse_up(display_window->get_mouse_x(), display_window->get_mouse_y());
                        }

                }

                if (display_window->get_mouse_x() || display_window->get_mouse_y()) { // mouse moved
                    for (auto &element : elements) {
                        element->on_mouse_move(display_window->get_mouse_x(), display_window->get_mouse_y());
                    }
                }

                if (display_window->get_keyboard_down()) {  // key down
                    for (auto &element : elements) {
                        element->on_key_down(display_window->get_keyboard_down());
                    }
                }

                if (display_window->get_keyboard_up()) { // key up
                    for (auto &element : elements) {
                        element->on_key_up(display_window->get_keyboard_up());
                    }
                }
            }

        private:
            std::chrono::high_resolution_clock::time_point previous_time;

            std::thread window_thread;
            bool is_multithreaded;
            std::shared_ptr<display_target> display_window;

        };
}

