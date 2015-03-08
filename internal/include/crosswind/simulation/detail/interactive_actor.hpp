#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL_events.h>

#include <crosswind/concurrent/mutex_container.hpp>
#include <crosswind/functional/delegate.hpp>
#include <crosswind/simulation/detail/mapping/event_mapping.hpp>

namespace cw{
namespace simulation{
namespace detail{

	class interactive_actor;

}// namespace detail
}// namespace simulation
}// namespace cw


class cw::simulation::detail::interactive_actor{
public:
	interactive_actor(){

	}

	virtual void handle_input(std::shared_ptr<platform::input::keyboard_listener> keyboard_listener) = 0;
 
    virtual void trigger(std::shared_ptr<event_mapping> event) = 0;

    template<typename T, typename U>
    void store_interactive_item(T& mm, const std::string& name, std::shared_ptr<U> new_Item){
        auto& container = mm.data.acquire();

        container[name] = new_Item;

        mm.data.release();
    }

    template<typename T>
    void swap_interactive_item(T& mm, const std::string& previous_item, const std::string& new_Item){
        auto& container = mm.data.acquire();

        if(container[previous_item] != container[new_Item]){
            container[previous_item] = container[new_Item];
        }

        mm.data.release();
    }

public:
    functional::delegate<void> on_mouse_down;
    functional::delegate<void> on_mouse_up;

protected:
    concurrent::mutex_map<std::string, std::shared_ptr<event_mapping> > events;
};// class image_actor