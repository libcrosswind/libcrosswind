#pragma once 

#include <memory>

#include <crosswind/core/concurrent/mutexed_container.hpp>
#include <crosswind/standard/simulation/standard_actor.hpp>
#include <crosswind/standard/simulation/interactive_actor.hpp>
#include <crosswind/standard/simulation/sdl_renderer.hpp>

namespace cw{
namespace standard{
namespace simulation{

	class stage;

}// namespace simulation
}// namespace standard
}// namespace cw


class cw::standard::simulation::stage{
public:
	stage(std::shared_ptr<standard::simulation::sdl_renderer> renderer): sdl_renderer(renderer) /* application(app)*/{

	}

	virtual void handle_stage_events(){

	}
	
	virtual void handle_input(SDL_Event* e){
/*		gui_elements.iterator([e](auto& element){
			element->handle_event(e);
		});*/

        auto& container = interactive_queue.data.acquire();

        for(auto& element: container){
           element->handle_event(e);
        }

		interactive_queue.data.release();
	}

	virtual void update(double delta){
		handle_stage_events();
/*		gui_elements.iterator([&delta](auto& element){
			element->update(delta);
		});*/

        auto& container = standard_queue.data.acquire();

        for(auto& element: container){
           element->update(delta);
        }

		standard_queue.data.release();
	}

	virtual void render(){
/*		gui_elements.iterator([sdl_renderer](auto& element){
			element->render(sdl_renderer);
		});*/
        auto& container = graphical_queue.data.acquire();

        for(auto& element: container){
           element->render(sdl_renderer);
        }

		graphical_queue.data.release();

	}

	core::concurrent::mutexed_vector<std::shared_ptr<interactive_actor> > interactive_queue;
	core::concurrent::mutexed_vector<std::shared_ptr<standard_actor>    > standard_queue;
	core::concurrent::mutexed_vector<std::shared_ptr<graphical_actor>   > graphical_queue;

protected:
/*	platform::generic::application* application;	*/
	std::shared_ptr<standard::simulation::sdl_renderer> sdl_renderer;
};// class stage