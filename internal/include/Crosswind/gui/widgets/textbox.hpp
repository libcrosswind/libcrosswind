#pragma once 

#include <Crosswind/pools/texture_pool.hpp>
#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/gui/widgets/detail/gui_element.hpp>

namespace cw{

	class textbox: public widget, public gui_element{

    public:
        textbox(){
            max_fps = 2;
            set_animation_status(false);
            set_animated(false);
            set_pressed(false);
            set_focus(false);

            set_text_color(128, 128, 128);

            switch_texture("current", 
                            texture_pool::loadTexture
                                ("textbox.png", get_width(), get_height(), get_theme() + "/" + "textbox"));

            switch_texture("previous", get_texture("current"));


            on_mouse_down += [this](int x, int y, int button){

                if(!this->get_pressed()){
                    if(this->contains_xy(x, y)){
                        this->set_pressed(true);
                        this->set_focus(true);
                    } else {
                        this->set_focus(false);
                    }
                }
            };

            on_mouse_move += [this](int x, int y){

                if(this->get_pressed()){

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

                if (this->get_pressed() && this->contains_xy(x, y)) {


                }


                this->set_pressed(false);
            };

            on_key_down += [this](int key){
                if(get_focus()){
                    std::string text = "";
                    std::string animation_character = "";

                    if(get_animated()){
                        text  = get_text().substr(0, get_text().size() - 1);
                        animation_character = get_text().substr(get_text().size() - 1, get_text().size());
                    } else {
                        text = get_text();
                    }

                    if(key >= 65 && key <= 90){
                        text += char(key);
                    } else if(key == 8){ //Backspace //@TODO create ascii keymap

                        text.size() > 0 ?
                        text  = text.substr(0, text.size() - 1):
                        text = "";

                    } else if (key == 13){ //Enter
                        //@TODO raise action command.
                    }

                    set_text(text + animation_character);
                }
            };
        }

        void update(double delta) override {

            frame_counter += delta;

            if (frame_counter >= (1.0f / max_fps)) {
                frame_counter = 0.f;

                if(get_focus()){
                    if(!get_animation_status()){

                        set_text(get_text() + "|");
                        set_animated(true);

                    } else {
                        if(get_animated()){
                            set_text(get_text().substr(0, get_text().size() - 1));
                        }

                        set_animated(false);
                    }

                    set_animation_status(!get_animation_status());
                } else {

                    if(get_animated()){
                        set_text(get_text().substr(0, get_text().size() - 1));
                    }

                    set_animation_status(false);
                    set_animated(false);

                }

            }


        }
    private:
        void set_animation_status(bool status){
            animation_status.store(status);
        }

        bool get_animation_status(){
            return animation_status.load();
        }


        void set_animated(bool status){
            animated.store(status);
        }

        bool get_animated(){
            return animated.load();
        }

        void set_pressed(bool status){
            pressed.store(status);
        }

        bool get_pressed(){
            return pressed.load();
        }

        void set_focus(bool status){
            focus.store(status);
        }

        bool get_focus(){
            return focus.load();
        }

    private:
        float frame_counter;
        unsigned short max_fps;
        std::atomic<bool> animation_status;
        std::atomic<bool> animated;
        std::atomic<bool> pressed;
        std::atomic<bool> focus;

    };

}