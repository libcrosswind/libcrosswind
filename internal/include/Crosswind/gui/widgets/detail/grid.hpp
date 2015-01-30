#pragma once

#include <mutex>
#include <memory>
#include <atomic>


#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/private/flag_set.hpp>
#include <Crosswind/events/delegate.hpp>

namespace cw{
	class grid: public virtual object_xyz{

    public:
        grid(): grid_offset(0.0){

        }

        void set_grid_offset(double offset){
            grid_offset.store(offset);
        }

        double get_grid_offset(){
            return grid_offset.load();
        }

        void set_grid_size(int size){
            grid_size.store(size);
        }

        int get_grid_size(){
            return grid_size.load();
        }

        void set_auto_resize(bool resize){
            auto_resize.store(resize);
        }

        bool get_auto_resize(){
            return auto_resize.load();
        }


    protected:
        std::atomic<double> grid_offset;

        std::atomic<bool> auto_resize;
        std::atomic<int> grid_size;
    };
}