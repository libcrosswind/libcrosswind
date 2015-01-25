#pragma once

#include <CImg/CImg.h>

namespace cw{
	class display_target{

	public:
		display_target(double width, double height, std::string text){
            window = std::shared_ptr<cimg_library::CImgDisplay>
						(new cimg_library::CImgDisplay(width, height, text.c_str()));
		}

        int get_mouse_button()  {   return window->button();         }
        int get_mouse_x()       {   return window->mouse_x();        }
        int get_mouse_y()       {   return window->mouse_y();        }
        int get_keyboard_up()   {   return window->key();            }
        int get_keyboard_down() {   return window->released_key();   }

        bool is_open()          {   return !window->is_closed();      }
		void display(cimg_library::CImg<unsigned char>& image){
            std::lock_guard<std::mutex> lock(window_mutex);
            window->display(image);
		}

	private:
        std::mutex window_mutex;
		std::shared_ptr<cimg_library::CImgDisplay> window;
	};
}