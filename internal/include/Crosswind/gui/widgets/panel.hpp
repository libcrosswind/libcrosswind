#pragma once 

#include <Crosswind/gui/widgets/detail/grid.hpp>
#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/pools/texture_pool.hpp>

namespace cw{

    class horizontal_group: public grid, public widget{
    public:
        horizontal_group(): major_x(0.0){

            textures.clear(); //Removing default textures.

            on_attached += [this](std::shared_ptr<widget> element){

                element->set_x(get_major_x()  + get_grid_offset());

            };
        }

        void set_major_x(double x){
            major_x.store(x);
        }

        double get_major_x(){
            set_major_x(this->get_x());

            for(auto& element: elements){
                if(element->get_x() > major_x.load()){
                    set_major_x(element->get_x() + element->get_width()/this->get_width());
                }
            }

            return major_x.load();
        }


        std::atomic<double> major_x;
    };

    class vertical_group: public grid, public widget{

    public:
        vertical_group(): major_y(0.0){

            textures.clear(); //Removing default textures.

            on_attached += [this](std::shared_ptr<widget> element){

                 element->set_y(get_major_y()  + get_grid_offset());

            };

        }

        void set_major_y(double y){
            major_y.store(y);
        }

        double get_major_y(){

            set_major_y(this->get_y());

            for(auto& element: elements){
                if(element->get_y() > major_y.load()){
                    set_major_y(element->get_y() + element->get_height()/this->get_height());
                }
            }

            return major_y.load();
        }

        void init(std::shared_ptr<init_flags> flags = nullptr){

        }

     private:
        std::atomic<double> major_y;
    };

    class panel: public grid, public widget, public gui_element{

    public:
        panel(){
            switch_texture("current", texture_pool::loadTexture("panel.png", get_width(), get_height(), get_theme() + "/" + "panel"));
            switch_texture("previous", get_texture("current"));
        }

        void show(){
            set_visible(true);
            switch_texture("current", textures["previous"]);
        }

        void hide(){
            set_visible(false);
            switch_texture("previous", textures["current"]);
            switch_texture("current", textures["blank"]);
        }


    };

}