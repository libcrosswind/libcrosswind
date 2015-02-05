#pragma once 

#include <Crosswind/gui/widgets/detail/grid.hpp>
#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/pools/texture_pool.hpp>

namespace cw{


    class panel: public grid, public widget{

    public:
        panel(){
            switch_texture("current", texture_pool::loadTexture("panel.png", get_width(), get_height(), get_theme() + "/" + "panel"));
            switch_texture("previous", get_texture("current"));

        }

        void show(){
            set_visible(true);
            switch_texture("current", get_texture("previous"));
        }

        void hide(){
            set_visible(false);
            switch_texture("previous", get_texture("current"));
            switch_texture("current", get_texture("blank"));
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