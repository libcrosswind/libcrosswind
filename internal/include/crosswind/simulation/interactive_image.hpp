#pragma once

#include <crosswind/javascript/json.hpp>
#include <crosswind/simulation/standard_image.hpp>

namespace cw{
namespace simulation{

	class interactive_image;

}// namespace simulation
}// namespace cw

class cw::simulation::interactive_image: public cw::simulation::standard_image, public cw::simulation::detail::interactive_actor{
public:
	interactive_image(	const geometry::point<int>& position,
        	            const geometry::point<int>& size, 
    	                const std::shared_ptr<platform::sdl::sdl_renderer> sdl_renderer,
	                    const std::string& template_file): standard_image(position, size, sdl_renderer, template_file){


		cw::javascript::json json;
 		json.from_file(template_file);

        auto& raw_json = json.data.acquire();


	    for (auto e = raw_json["events"].begin_members(); e != raw_json["events"].end_members(); ++e)
        {
            auto mapping = std::make_shared<detail::event_mapping>();
            mapping->what = e->value()["what"].as<std::string>();
            mapping->action = e->value()["action"].as<std::string>();
            mapping->which = e->value()["which"].as<std::string>();

            store_interactive_item(events, e->name(), mapping);
        }


        json.data.release();


	}

	void handle_event(SDL_Event* e){
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
                        on_mouse_down();
					break;
					
					case SDL_MOUSEBUTTONUP:
                        trigger(events("on_mouse_up"));
                        on_mouse_up();
                    break;

				}

			} else {//Mouse is outside button
                trigger(events("on_mouse_out"));
			}

		}
	}

    void trigger(std::shared_ptr<detail::event_mapping> event){
         if(event->what == "animation"){
            if(event->action == "start"){
				swap_graphical_item(animations, "current", event->which);
            }
        }
    }

};// class interactive_image

