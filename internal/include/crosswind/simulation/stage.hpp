#pragma once 

#include <memory>
#include <type_traits>

#include <crosswind/concurrent/mutex_property.hpp>
#include <crosswind/concurrent/mutex_container.hpp>
#include <crosswind/platform/sdl/sdl_gl_renderer.hpp>
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
	stage()/*: application(app)*/{

	}

    virtual void init(std::shared_ptr<cw::platform::sdl::sdl_gl_renderer> sdl_gl_renderer,
            std::shared_ptr<cw::platform::sdl::sdl_audio_system> sdl_audio_system) = 0;

	virtual void handle_stage_events(){
		auto& container = event_queue.data.acquire();

		for(auto& event : container){
			event();
		}

		container.clear();

		event_queue.data.release();
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

	virtual void render(std::shared_ptr<platform::sdl::sdl_gl_renderer> sdl_gl_renderer){

        auto& container = graphical_queue.data.acquire();

		for(auto& element: container){
           element->render(sdl_gl_renderer);
        }

		graphical_queue.data.release();

	}



	template<typename T>
	void add(std::shared_ptr<T> actor){

		if(std::is_base_of<detail::interactive_actor, T>()){
			add(std::dynamic_pointer_cast<detail::interactive_actor>(actor));
		}

		if(std::is_base_of<detail::standard_actor, T>()){
			add(std::dynamic_pointer_cast<detail::standard_actor>(actor));
		}
		
		if(std::is_base_of<detail::graphical_actor, T>()){
			add(std::dynamic_pointer_cast<detail::graphical_actor>(actor));
		}
	}

	void add(std::shared_ptr<detail::interactive_actor> actor){
		interactive_queue.push_back(actor);
	}

	void add(std::shared_ptr<detail::standard_actor> actor){
		standard_queue.push_back(actor);
	}

	void add(std::shared_ptr<detail::graphical_actor> actor){
		graphical_queue.push_back(actor);
	}

	void post_event(const std::function<void()>& event){
		event_queue.push_back(event);
	}

    concurrent::mutex_property<std::string> name;

protected:
	concurrent::mutex_vector<std::shared_ptr<detail::interactive_actor> > interactive_queue;
	concurrent::mutex_vector<std::shared_ptr<detail::standard_actor>    > standard_queue;
	concurrent::mutex_vector<std::shared_ptr<detail::graphical_actor>   > graphical_queue;
	concurrent::mutex_vector<std::function<void()> > event_queue;


protected:
/*	platform::generic::application* application;	*/

};// class stage