#pragma once

#include <mutex>
#include <memory>

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

    protected:
        std::atomic<double> grid_offset;

    };
}