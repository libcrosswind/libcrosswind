#pragma once

#include <string> 
#include <thread> 
#include <atomic> 

#include <Crosswind/input/input_listener.hpp>
#include <Crosswind/pools/texture_pool.hpp>
#include <Crosswind/events/delegate.hpp>

#include <Crosswind/concurrency/atomical_property.hpp>
#include <Crosswind/concurrency/mutexed_property.hpp>

#include <Crosswind/containers/cacheable.hpp>

namespace cw{



    class renderable {

    public:
        virtual void render(std::shared_ptr<texture> render_texture){

            if(textures.load("current")){

                textures.load("current")->draw_text(get_absolute_width()/2 ,
                        get_absolute_height()/2,
                        get_text(),
                        get_text_color());

                textures.load("current")->render_to_target(get_absolute_x(), get_absolute_y(), render_texture);
            }
        }

    };

    class render_bin: public renderable{

        virtual void render(std::shared_ptr<texture> render_texture) override {
            for(auto& element : elements){
                element->render(render_texture);
            }
        }

        void attach(std::shared_ptr<renderable> element){
            elements.push_back(element);
        }

        void detach(std::shared_ptr<renderable> element){
        }

        std::vector<std::shared_ptr<rendereable> > elements; //Attached elements.
    };


    class widget{

    public:
        widget(){

           /* sprite.textures.source += [this](std::string path){

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

            };*/

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


}