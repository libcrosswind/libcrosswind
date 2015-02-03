#pragma once 

#include <Crosswind/pools/texture_pool.hpp>
#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/gui/widgets/detail/gui_element.hpp>

namespace cw{

	class button: public widget, public gui_element{

    public:
        button(){

            switch_texture("on", texture_pool::loadTexture("button_on.png", get_width(), get_height(), get_theme() + "/" + "button"));
            switch_texture("off", texture_pool::loadTexture("button_on.png", get_width(), get_height(), get_theme() + "/" + "button"));
            switch_texture("current", get_texture("off"));
            switch_texture("previous", get_texture("current"));

            //TODO
            //textures["hover"];

            on_mouse_down += [this](int x, int y, int button){

                if(!this->pressed.load()){
                    if(this->contains_xy(x, y)){
                        this->pressed.store(true);
                        this->switch_texture("current", textures["on"]);
                    }
                }

            };

            on_mouse_move += [this](int x, int y){

                if(this->pressed.load()){

                    if(this->get_draggable()){
                        this->set_x(x);
                        this->set_y(y);
                    }

                } else {
                    if (this->contains_xy(x, y)) {
                        //this->switch_texture("hover", textures["on"]); //TODO
                    }
                }

            };

            on_mouse_up += [this](int x, int y){

                if (pressed.load() && this->contains_xy(x, y)) {
                    on_clicked();
                }

                pressed.store(false);
                switch_texture("current", textures["off"]);

            };
        }

    private:
        std::atomic<bool> pressed;

    };

}