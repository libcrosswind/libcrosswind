#pragma once 


namespace cw{
    class label: public widget, public gui_element{

    public:
        label(){

            //TODO move mouse implementations to widget class and create textures for on, off, visible, hidden textures.
            //TODO add transparent mask to rendering texture.
            set_text_color(128, 128, 128);

            switch_texture("text",
                    texture_pool::loadTexture("label.png", get_width(), get_height(), get_theme() + "/" + "label"));

            switch_texture("current", get_texture("text"));
            on_mouse_down += [this](int x, int y, int button){

                if(!this->pressed.load()){
                    if(this->contains_xy(x, y)){
                        this->pressed.store(true);
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

            };
        }

    private:
        std::atomic<bool> pressed;

    };
}