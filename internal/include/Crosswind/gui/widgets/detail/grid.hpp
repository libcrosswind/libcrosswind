#pragma once

#include <mutex>
#include <memory>

#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/private/flag_set.hpp>
#include <Crosswind/events/delegate.hpp>

namespace cw{
	class grid: public virtual object_xyz{

    public:

        grid(): x_offset(0.0), y_offset(0.0){

        }

        void set_x_offset(double offset){
            x_offset.store(offset);
        }

        double get_x_offset(){
            return x_offset.load();
        }

        void set_y_offset(double offset){
            y_offset.store(offset);
        }

        double get_y_offset(){
            return y_offset.load();
        }

        void attach(std::shared_ptr<widget> element) {
            std::lock_guard<std::mutex> lock(element_mutex);
            elements.push_back(element);
            on_attached(element);
        }

        void detach(std::shared_ptr<widget> element){
            std::lock_guard<std::mutex> lock(element_mutex);//TODO
        }

    protected:
        delegate<std::shared_ptr<widget> > on_attached;
        delegate<std::shared_ptr<widget> > on_detached;

        std::vector<std::shared_ptr<widget>> elements; //Attached elements.

        std::atomic<double> x_offset;
        std::atomic<double> y_offset;
    private:
        std::mutex element_mutex;

    };
}