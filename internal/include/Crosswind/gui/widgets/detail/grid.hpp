#pragma once

#include <mutex>
#include <memory>

#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/private/flag_set.hpp>
namespace cw{
	class grid{

public:
       
       
       enum attach_position{
            CENTERED = 1 << 0,
            LEFT     = 1 << 1,
            RIGHT    = 1 << 2
       }; 

       void attach(std::shared_ptr<widget> element) {
            std::lock_guard<std::mutex> lock(element_mutex);
            elements.push_back(element);
        }

        void detach(std::shared_ptr<widget> element){
            std::lock_guard<std::mutex> lock(element_mutex);//TODO

        }

protected:
	 std::vector<std::shared_ptr<widget>> elements; //Attached elements.

private:
     std::mutex element_mutex;
       
	};
}