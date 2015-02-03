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

                adjust_size();
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

        void adjust_size(){

            int major_height =  this->get_height();
            int total_width = 0;

            for(auto& element: elements){
                if(element->get_height() >= major_height){
                    major_height = element->get_width();
                    major_height += get_grid_offset();
                }

                total_width += get_grid_offset();
                total_width = element->get_height();
            }


            this->set_width(major_height);
            this->set_height(total_width);

        }
    private:
        std::atomic<double> major_x;
    };

    class vertical_group: public grid, public widget{

    public:
        vertical_group(): major_y(0.0){

            textures.clear(); //Removing default textures.

            on_attached += [this](std::shared_ptr<widget> element){

                 adjust_size();
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
                    set_major_y(element->get_y() + element->get_height());
                    std::cout<<"Relation: "<<element->get_height()<<"/"<<this->get_height()<<std::endl;
                    std::cout<<this->get_y()<<std::endl;
                    std::cout<<major_y.load()<<std::endl;
                }
            }

            return major_y.load();
        }


        void adjust_size(){

            int major_width =  this->get_width();
            int total_height = 0;

            for(auto& element: elements){
                if(element->get_width() >= major_width){
                    major_width = element->get_width();
                    major_width += get_grid_offset();
                }

                total_height += get_grid_offset();
                total_height = element->get_height();
            }


            this->set_width(major_width);
            this->set_height(total_height);

        }

     private:
        std::atomic<double> major_y;
    };

    class panel: public grid, public widget{

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

        void adjust_size(){

            /*
            //@TODO get_auto_resize, move major methods to grid class.
            int major_width =  this->get_width();
            int total_height = 0;

            for(auto& element: elements){
                if(element->get_width() >= major_width){
                    major_width = element->get_width();
                    major_width += get_grid_offset();
                }

                total_height += get_grid_offset();
                total_height = element->get_height();
            }


            this->set_width(major_width);
            this->set_height(total_height);*/

        }
    };

}