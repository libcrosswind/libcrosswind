#pragma once 

#include <memory>
#include <type_traits>

#include <crosswind/concurrent/mutex_property.hpp>
#include <crosswind/concurrent/mutex_container.hpp>

#include <crosswind/platform/backend/interface/engine.hpp>
#include <crosswind/platform/backend/interface/core/input_listener.hpp>

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

    virtual void init(std::shared_ptr<platform::backend::interface::engine> engine) = 0;
    virtual void deinit(std::shared_ptr<platform::backend::interface::engine> engine) = 0;


    virtual void handle_stage_events(){
		auto& container = event_queue.data.acquire();
		std::vector<std::pair<bool, std::function<void()> > > continuous_events;

		for(auto& event_mapping : container){

			if(event_mapping.first == true){
				continuous_events.push_back(event_mapping);
			}

			event_mapping.second();
		}


		container.clear();
		container.insert(container.end(), continuous_events.begin(), continuous_events.end());
		event_queue.data.release();
	}
	
	virtual void handle_input(std::shared_ptr<platform::backend::interface::core::input_listener> input_listener){

		auto& container = interactive_queue.data.acquire();

		for(auto& element: container){
           element->handle_input(input_listener);
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
           element->draw();
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

	void post_event(const std::function<void()>& event, const bool& continuous = false){
		event_queue.push_back(std::make_pair(continuous, event));
	}

    concurrent::mutex_property<std::string> name;

protected:
	concurrent::mutex_vector<std::shared_ptr<detail::interactive_actor> > interactive_queue;
	concurrent::mutex_vector<std::shared_ptr<detail::standard_actor>    > standard_queue;
	concurrent::mutex_vector<std::shared_ptr<detail::graphical_actor>   > graphical_queue;
	concurrent::mutex_vector<std::pair<bool, std::function<void()> > > event_queue;


protected:
/*	platform::generic::application* application;	*/

};// class stage