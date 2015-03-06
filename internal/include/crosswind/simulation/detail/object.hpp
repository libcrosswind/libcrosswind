#pragma once

#include <vector>

namespace cw{
namespace simulation{
namespace detail{

    class object;

}// namespace detail
}// namespace simulation
}// namespace cw

class cw::simulation::detail::object{
public:
    object(const math::vector3& p, const math::vector3& s):
    position(p), size(s){

    }

protected:
    std::vector<float> vertices;
    math::vector3 position;
    math::vector3 size;
};// class object


/*
    class widget{

    public:
        widget(){

           sprite.textures.source += [this](std::string path){

                return texture_pool::loadTexture
                        (path, this->get_width(), this->get_height());

            };

            sprite.textures.store("current", std::shared_ptr<texture>(new texture(get_width(), get_height(), 1.0, 4)));

            on_mouse_down += [this](int x, int y, int button){

                if(!this->pressed()){
                    if(this->transform.contains_xy(x, y)){
                        this->pressed = true;
                        this->switch_texture("current", get_texture("on"));
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

                if (pressed() && this->contains_xy(x, y)) {
                    on_clicked();
                }

                this->pressed = false;
                switch_texture("current", get_texture("off"));

            };


            on_mouse_down += [this](int x, int y, int button){

                if(!this->pressed()){
                    if(this->contains_xy(x, y)){
                        this->pressed = true;
                    }
                }

            };

            on_mouse_up += [this](int x, int y){

                if (this->pressed() && this->contains_xy(x, y)) {
                    on_clicked();
                }

                this->pressed = false;

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

                for(auto& element : elements){
                    element->on_mouse_up(x, y);
                }

            };

            on_key_down += [this](int key){

                for(auto& element : elements){
                    element->on_key_down(key);
                }

            };

        }


public:
        //Properties
        mutexed_property<std::string> name;

        detail::text text;
        graphics::sprite sprite;

        input_handler input;

        //Delegates

    };
*/

