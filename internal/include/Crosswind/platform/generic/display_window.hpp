#pragma once

#include <CImg/CImg.h>

namespace cw{
namespace platform{
namespace generic{
    
    class display_window;

}// namespace generic 
}// namespace platform
}// namespace cw

class cw::plaform::generic::display_window{

public:
    display_window(double width, double height, std::string text){
        window_wrapper = cimg_library::CImgDisplay(width, height, text.c_str());
    }

    void wait(int ms){
        window_wrapper.wait(ms);
    }

    int get_mouse_button()  {   return window_wrapper.button();          }
    int get_mouse_x()       {   return window_wrapper.mouse_x();         }
    int get_mouse_y()       {   return window_wrapper.mouse_y();         }
    int get_keyboard_up()   {   return window_wrapper.key();             }
    int get_keyboard_down() {   return window_wrapper.released_key();    }

    bool is_open()          {   return !window_wrapper.is_closed();      }

    void display(standard::drawing::texture& texture){

        auto& target_texture = texture.data.acquire();

        window_wrapper.display(target_texture);

        texture.data.release();
    }

private:
    cimg_library::CImgDisplay window_wrapper;
};