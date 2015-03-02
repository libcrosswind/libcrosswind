#pragma once 

#include <memory>
#include <type_traits>

#include <crosswind/concurrent/mutex_container.hpp>
#include <crosswind/platform/sdl/sdl_renderer.hpp>
#include <crosswind/simulation/detail/standard_actor.hpp>
#include <crosswind/simulation/detail/interactive_actor.hpp>
#include <crosswind/simulation/detail/graphical_actor.hpp>

namespace cw{
namespace simulation{

	class stage;

}// namespace simulation
}// namespace cw


class cw::simulation::stage{
public:
	stage(std::shared_ptr<platform::sdl::sdl_renderer> renderer): sdl_renderer(renderer) /* application(app)*/{

	}

	virtual void handle_stage_events(){

	}
	
	virtual void handle_input(SDL_Event* e){

		auto& container = interactive_queue.data.acquire();

		for(auto& element: container){
           element->handle_event(e);
        }

		interactive_queue.data.release();
	}

	virtual void update(double delta){

        auto& container = standard_queue.data.acquire();

		for(auto& element: container){
           element->update(delta);
        }

		standard_queue.data.release();
	}

	virtual void render(){

        auto& container = graphical_queue.data.acquire();

		for(auto& element: container){
           element->render(sdl_renderer);
        }

		graphical_queue.data.release();

	}

	template<typename T>
	void add(std::shared_ptr<T> actor){

		if(std::is_base_of<detail::interactive_actor, T>()){
			interactive_queue.push_back(actor);
		}

		if(std::is_base_of<detail::standard_actor, T>()){
			standard_queue.push_back(actor);
		}
		
		if(std::is_base_of<detail::graphical_actor, T>()){
			graphical_queue.push_back(actor);
		}
	}

protected:
	concurrent::mutex_vector<std::shared_ptr<detail::interactive_actor> > interactive_queue;
	concurrent::mutex_vector<std::shared_ptr<detail::standard_actor>    > standard_queue;
	concurrent::mutex_vector<std::shared_ptr<detail::graphical_actor>   > graphical_queue;

protected:
/*	platform::generic::application* application;	*/
	std::shared_ptr<platform::sdl::sdl_renderer> sdl_renderer;
};// class stage