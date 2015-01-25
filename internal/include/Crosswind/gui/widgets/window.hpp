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
            window(){
            }

            void init(FlagSet<InitFlags> flags = FlagSet<InitFlags>()){
                init_flags = flags;

                textures["blank"] = std::shared_ptr<texture>(new texture(get_width(), get_height(), get_depth(), 4));
                textures["render"]= std::shared_ptr<texture>(new texture(get_width(), get_height(), get_depth(), 4));

                previous_time = std::chrono::high_resolution_clock::now();
            }

            void show(){
                set_visible(true);
                display_window =
                        std::shared_ptr<display_target>(new display_target(get_width(), get_height(), get_text()));

                on_show();

                if(init_flags.test(IN_NEW_THREAD)){
                    widget_thread = std::thread(&widget::loop, this);
                } else {
                    loop();
                }

            }

            void hide(){
                set_visible(false);
                on_hide();
            }

            void update(double delta){

           /*     frame_counter += delta;

                if (frameCounter >= (max_fps)) {
                    frameCounter = 0.f;
                }
            */

                for(auto& element : elements)
                    element->update(delta);


            }

            void render(std::shared_ptr<texture> render_texture){

                textures["blank"]->render_to_target(0, 0, render_texture);

                for(auto& element : elements){
                    element->render(render_texture);
                }

                render_texture->render_to_display(display_window);

            }

            void loop() {

                while (get_visible() && display_window->is_open() ) {

                    handle_input();

                    update(get_delta());

                    texture_mutex.lock();
                    render(textures["render"]);
                    texture_mutex.unlock();

                    //draw_text(100,100,"Hello World",purple); // Draw a purple "Hello world" at coordinates (100,100).

                    //display.wait(20);
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
                            element->on_mouse_up();
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
        //    unsigned short max_fps;
        //    double frame_counter;

            std::shared_ptr<display_target> display_window;

        };
}

