#pragma once 

#include <memory>

#include <crosswind/core/concurrent/mutexed_container.hpp>
#include <crosswind/standard/simulation/image_actor.hpp>

namespace cw{
namespace standard{
namespace simulation{

	class stage;

}// namespace simulation
}// namespace standard
}// namespace cw


class cw::standard::simulation::stage{
public:
	stage(/*cw::platform::generic::application* app*/)/*: application(app)*/{

	}

	virtual void handle_stage_events(){

	}
	
	virtual void handle_input(SDL_Event* e){
/*		gui_elements.iterator([e](auto& element){
			element->handle_event(e);
		});*/

        auto& container = gui_elements.data.acquire();

        for(auto& element: container){
           element->handle_event(e);
        }

        gui_elements.data.release();
	}

	virtual void update(double delta){
		handle_stage_events();
/*		gui_elements.iterator([&delta](auto& element){
			element->update(delta);
		});*/

        auto& container = gui_elements.data.acquire();

        for(auto& element: container){
           element->update(delta);
        }

        gui_elements.data.release();



	}

	virtual void render(std::shared_ptr<standard::simulation::sdl_renderer> sdl_renderer){
/*		gui_elements.iterator([sdl_renderer](auto& element){
			element->render(sdl_renderer);
		});*/
        auto& container = gui_elements.data.acquire();

        for(auto& element: container){
           element->render(sdl_renderer);
        }

        gui_elements.data.release();


	}

//	concurrent::mutexed_vector<std::shared_ptr<audio_actor> > sound_elements;
	core::concurrent::mutexed_vector<std::shared_ptr<image_actor> > gui_elements;
//	concurrent::mutexed_vector<std::shared_ptr<mesh_actor> > spatial_elements;

protected:
/*	platform::generic::application* application;	*/
};// class stage