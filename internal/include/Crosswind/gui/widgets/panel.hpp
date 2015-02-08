#pragma once 

#include <Crosswind/gui/widgets/detail/grid.hpp>
#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/pools/texture_pool.hpp>

namespace cw{


    class panel: public grid, public widget{

    public:
        panel(){

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