#pragma once

#include <CImg/CImg.h>

#include <functional>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>

#include <Crosswind/gui/widgets/detail/widget.h>
#include <Crosswind/events/delegate.h>

namespace cw{
	
	class window{

	public:

	    window() = delete;

	    window(int w, int h, std::string name):
	            width(w), height(h),
	            background(w, h, 1, 4, 0), blank(w, h, 1, 4, 0),
	            window_name(name),
	            run(false){


	    }

	    int& getWidth() { return width; }
	    int& getHeight() { return height; }

	    void show(){
	        run = true;
	        display = cimg_library::CImgDisplay(background, window_name.c_str());
	        loop();
	    }

	    void close(){
	        run = false;
	    }

	    void loop(){

	        while (!display.is_closed() && run) {

	            if (display.button()) { // button clicked. //TODO reduce iterations and implement Z-order.
	                std::for_each(elements.begin(), elements.end(), [this](std::shared_ptr<widget> element){

                        if(element->containsXY(display.mouse_x(), display.mouse_y())){
                            element->on_mouse_down(display.button());
                        }

	                });
	            } else {
                    std::for_each(elements.begin(), elements.end(), [this](std::shared_ptr<widget> element){

                        if(element->containsXY(display.mouse_x(), display.mouse_y())){
                            element->on_mouse_up();
                        }

                    });
	            }

	            if(display.mouse_x() || display.mouse_y()){ // mouse moved

	                std::for_each(elements.begin(), elements.end(), [this](std::shared_ptr<widget> element){
	                        element->on_mouse_move(display.mouse_x(), display.mouse_y());
	                });

	            }

	            if(display.key()){  // key down

	                std::for_each(elements.begin(), elements.end(), [this](std::shared_ptr<widget> element){
	                        element->on_key_down(display.key());
	                });
	            }

	            if(display.released_key()){ // key up
	                std::for_each(elements.begin(), elements.end(), [this](std::shared_ptr<widget> element){
	                        element->on_key_up(display.released_key());
	                });
	            }


	            std::for_each(elements.begin(), elements.end(), [this](std::shared_ptr<widget> element){
	                    element->on_key_up(display.released_key());
	            });


	            std::for_each(elements.begin(), elements.end(), [this](std::shared_ptr<widget> element){
	              //  if(element->updateLogic)//@TODO implement logic element interface.
	                    element->updateLogic();
	            });


	            background.draw_image(0, 0, blank);

	            std::for_each(elements.begin(), elements.end(), [this](std::shared_ptr<widget> element){
	                background.draw_image(element->getX(), element->getY(), element->getSprite());
	            });

	            display.display(background);
	            display.wait(20);
	        }

            on_closed();

	    }


	    void attach(std::shared_ptr<widget> element){
	        elements.push_back(element);
	    }

        delegate<> on_closed;

	    cimg_library::CImgDisplay display;
	    cimg_library::CImg<unsigned char> background;
	    cimg_library::CImg<unsigned char> blank;


	private:
	    int width, height;
	    std::string window_name;
	    std::vector<std::shared_ptr<widget>> elements;
	    bool run;
	};



}

