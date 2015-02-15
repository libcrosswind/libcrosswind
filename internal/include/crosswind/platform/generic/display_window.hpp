#pragma once

#include <chrono>

#include <CImg/CImg.h>

#include <crosswind/standard/geometry/rectangle.hpp>
#include <crosswind/standard/drawing/texture.hpp>

namespace cw{
namespace platform{
namespace generic{
    
    class display_window;

}// namespace generic 
}// namespace platform
}// namespace cw

class cw::platform::generic::display_window{

public:
    display_window(double width, double height, std::string text): 
    render_texture(width, height),
    window_wrapper(width, height, text.c_str()){

        buffering_key = false;
        buffered_key = 0;
        key_buffer_counter = 0.0f;
        key_buffer_frames = 1.0f;

    }

    void wait(int ms){
        window_wrapper.wait(ms);
    }

    int get_mouse_button()  {   return window_wrapper.button();          }
    int get_mouse_x()       {   return window_wrapper.mouse_x();         }
    int get_mouse_y()       {   return window_wrapper.mouse_y();         }
    int get_keyboard_down() {   return window_wrapper.released_key();    }
    int get_keyboard_up()   {   return window_wrapper.key();             }

    bool is_open()          {   return !window_wrapper.is_closed();      }

    void refresh(){
        double delta = get_delta();
        //handle_input(delta);

        render_texture.clear();

        /*for(auto& element : elements){
            element->update(delta);
        }*/

        /*for(auto& element : elements){
            element->render(render_texture);
        }*/

        auto& target_texture = render_texture.data.acquire();

        window_wrapper.display(target_texture);

        render_texture.data.release();
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

private:
    standard::drawing::texture<unsigned char> render_texture;
    cimg_library::CImgDisplay window_wrapper;

    std::chrono::high_resolution_clock::time_point previous_time;

    core::concurrent::atomical_property<bool>  buffering_key;
    core::concurrent::atomical_property<int>   buffered_key;
    core::concurrent::atomical_property<float> key_buffer_counter;
    core::concurrent::atomical_property<float> key_buffer_frames;

    /*void handle_input(double delta) {

        //TODO implement z-order.
        int mouse_button = this->get_mouse_button();
        int mouse_x      = this->get_mouse_x();
        int mouse_y      = this->get_mouse_y();
        int key_down     = this->get_keyboard_down();
        int key_up       = this->get_keyboard_up();

        for (auto &element:elements) {

            if (mouse_button) {
                //Send mouse down event to all elements;
                element->on_mouse_down( mouse_x,
                        mouse_y,
                        mouse_button);
            } else {
                //Send mouse released event to all elements.
                element->on_mouse_up(mouse_x, mouse_y);
            }
       
            if (mouse_x || mouse_y) { // mouse moved
                element->on_mouse_move(mouse_x, mouse_y);
            }

            if (key_down) {  
                if(key_down != buffered_key){
                    if(!buffering_key){
                        element->on_key_down(key_down);
                        key_buffer_counter = 0.0f;
                        buffering_key = true;
                        buffered_key = key_down;
                    }// !buffering_key
                } else {
                    if(buffering_key){
                        key_buffer_counter += delta;
                         if(key_buffer_counter >= (1.0f/ key_buffer_frames){
                             key_buffer_counter = 0.0f;
                             buffering_key = false;
                         }
                    } else {
                        element->on_key_down(key_down);
                    }
                }

            } else {
                buffered_key = 0;
            }

            if (key_up) { // key up
                key_buffer_counter = 0.0f;
                buffering_key = false;
                buffered_key = 0;
                element->on_key_up(window->get_keyboard_up());  
            }   

        }
    }*/

};