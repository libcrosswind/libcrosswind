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


#include <Crosswind/private/flag_set.hpp>

namespace cw{

    class window: public grid, public widget, public gui_element {

    public: //TODO move this to window detail flags.
        class init_flags{
        public:
            init_flags(){

                method = [](){
                    return [](int test_flags){
                        return false;
                    };

                }();

            }

            template<typename T>
            void set(T flag_pack){

                method = [&flag_pack](){
                    std::shared_ptr<flag_set<T> > flags(new flag_set<T>(flag_pack));

                    return [flags](int test_flags){
                        return flags->test((T)test_flags);
                    };

                }();
            }

            bool has(int flag_pack){
                return method(flag_pack);
            }

        protected:
            std::function<bool(int)> method;
        };




    public:
            enum window_flags{
                MULTITHREADED = 1 << 0
            };

            window(std::shared_ptr<init_flags> flags = nullptr): is_multithreaded(false){

                if(flags){
                    flags->has(window_flags::MULTITHREADED)? is_multithreaded = true: is_multithreaded = false;
                }

                switch_texture("render", std::shared_ptr<texture>(new texture(get_width(), get_height(), get_depth(), 4)));


                set_buffering(false);
                set_buffer_key(0);
                set_buffer_counter(0.0);
                set_buffer_frames(1);


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

/*            void update(double delta) override {
                    frame_counter += delta;

                     if (frameCounter >= (max_fps)) {
                         frameCounter = 0.f;
                     }

            }*/

        void render(std::shared_ptr<texture> render_texture) override {

                render_texture->clear();

                for(auto& element : elements){
                    element->render(render_texture);
                }

                render_texture->render_to_display(display_window);

            }

            void loop() override {

                while (get_visible() && display_window->is_open() ) {

                    double delta = get_delta();

                    handle_input(delta);

                    update(delta);

                    render(get_texture("render"));

                    display_window->wait(10);

                }

                on_hide();
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

            void handle_input(double delta) {

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

                if (display_window->get_keyboard_down()) {  // key down //@TODO single reads for atomics.

                    if(display_window->get_keyboard_down() != get_buffer_key()){
                        if(!get_buffering()){  //@TODO implement buffering for keypress

                            for (auto &element : elements) {
                                element->on_key_down(display_window->get_keyboard_down());
                            }

                            set_buffer_counter(0.0f);
                            set_buffering(true);
                            set_buffer_key(display_window->get_keyboard_down());
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
                                element->on_key_down(display_window->get_keyboard_down());
                            }
                        }
                    }


                } else {
                    set_buffer_key(0);
                }

                if (display_window->get_keyboard_up()) { // key up
                    set_buffer_counter(0.0f);
                    set_buffering(false);
                    set_buffer_key(0);

                    for (auto &element : elements) {
                        element->on_key_up(display_window->get_keyboard_up());
                    }
                }
            }


    protected:
        void set_buffering(bool status){
            buffering.store(status);
        }

        bool get_buffering(){
            return buffering.load();
        }

        void set_buffer_key(int key){
            buffer_key.store(key);
        }

        int get_buffer_key(){
            return buffer_key.load();
        }

        void set_buffer_counter(float counter){
            buffer_counter.store(counter);
        }

        int get_buffer_counter(){
            return buffer_counter.load();
        }

        void set_buffer_frames(float frames){
            buffer_frames.store(frames);
        }

        float get_buffer_frames(){
            return buffer_frames.load();
        }



    private:
        std::chrono::high_resolution_clock::time_point previous_time;

        std::atomic<bool> buffering;
        std::atomic<int> buffer_key;
        std::atomic<float> buffer_counter;
        std::atomic<float> buffer_frames;

        std::thread window_thread;
        bool is_multithreaded;
        std::shared_ptr<display_target> display_window;

    };
}

