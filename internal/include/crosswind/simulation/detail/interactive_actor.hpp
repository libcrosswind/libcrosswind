#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL_events.h>

#include <crosswind/core/concurrent/mutexed_map.hpp>

namespace cw{
namespace simulation{

	class interactive_actor;

}// namespace simulation
}// namespace cw


class cw::simulation::interactive_actor{
public:
	interactive_actor(){

	}

	virtual void handle_event(SDL_Event* e){

		//If mouse event happened
		if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
			//Get mouse position
			int x, y;
			SDL_GetMouseState( &x, &y );

			if(bounds.contains_xy(x, y)){ //Mouse is inside button
				//Set mouse over sprite
				switch(e->type){

					case SDL_MOUSEMOTION:
                        trigger(events("on_mouse_over"));
					break;
				
					case SDL_MOUSEBUTTONDOWN:
                        trigger(events("on_mouse_down"));
					break;
					
					case SDL_MOUSEBUTTONUP:
                        trigger(events("on_mouse_up"));
					break;

				}

			} else {//Mouse is outside button
                trigger(events("on_mouse_out"));
			}

		}
	}

    virtual void trigger(std::shared_ptr< event_mapping > event){

         if(event->what == "animation"){
            if(event->action == "start"){
                //swap_animation("current", event->which);
            }
        }
    }

    void load_event(const std::string& name, std::shared_ptr<event_mapping> new_event){
        auto& e = events.data.acquire();

        e[name] = new_event;

        events.data.release();
    }

    void swap_event(const std::string& previous_event, const std::string& new_event){
        auto& e = events.data.acquire();

        if(e[previous_event] != e[new_event]){
            e[previous_event] = e[new_event];
        }

        events.data.release();
    }

private:
    core::concurrent::mutexed_map<std::string, std::shared_ptr< event_mapping     > > events;

   // core::functional::delegate<void> on_mouse_click;
};// class image_actor