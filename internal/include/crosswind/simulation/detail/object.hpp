#pragma once

#include <crosswind/standard/geometry/point.hpp>
#include <crosswind/standard/geometry/rectangle.hpp>

namespace cw{
namespace simulation{
namespace detail{

    class object;

}// namespace detail
}// namespace simulation
}// namespace cw

class cw::simulation::detail::object{
public:
    object(const standard::geometry::point<int>& position, const standard::geometry::point<int>& size):
    bounds(position.x, position.y, size.x, size.y){

    }

	standard::geometry::rectangle<int> bounds;
};


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

            on_dimension_set += [this](){
                std::lock_guard<std::mutex> lock(texture_mutex);

            };

            std::function<void(std::map<std::string, std::shared_ptr<texture> >)>
                    resize_manipulation = [this](std::map<std::string, std::shared_ptr<texture> > textures){
                                        for(auto& texture : textures){
                                            texture.second->resize(this->get_width(), this->get_height());
                                        }
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

            on_mouse_down += [this](int x, int y, int button){

                for(auto& element : elements){
                    element->on_mouse_down(x, y, button);
                }

            };

            on_mouse_move += [this](int x, int y){

                for(auto& element : elements){
                    element->on_mouse_move(x, y);
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


        virtual void update(double delta){

            for(auto& element : elements){
                element->update(delta);
            }
        }

public:
        //Properties
        atomical_property<bool> draggable;
        atomical_property<bool> pressed;
        mutexed_property<std::string> name;

        detail::text text;
        graphics::sprite sprite;

        input_handler input;

        //Delegates
        delegate<void> on_clicked;

    };
*/

