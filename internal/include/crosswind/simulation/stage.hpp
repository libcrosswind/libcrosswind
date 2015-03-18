#pragma once 

#include <memory>
#include <type_traits>

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
		std::vector<std::pair<bool, std::function<void()> > > continuous_events;

		for(auto& event_mapping : event_queue){

			if(event_mapping.first == true){
				continuous_events.push_back(event_mapping);
			}

			event_mapping.second();
		}


		event_queue.clear();
		event_queue.insert(event_queue.end(), continuous_events.begin(), continuous_events.end());
	}
	

	virtual void update(double delta){

		for(auto& element: standard_queue){
           element->update(delta);
        }
	}

	virtual void render(){

        renderer->begin();

        renderer->set_uniform_matrix("projection_matrix", camera_list["current"]->get_camera_matrix());

        for(auto& model_mapping : model_list){
            for(auto& sprite_mapping : model_mapping.second->sprites){
                renderer->upload(sprite_mapping.second);
            }
        }

        renderer->end();

	}

	virtual void draw(){

		for(auto& element: graphical_queue){
           element->draw();
        }

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

    std::string name;

protected:
	std::vector<std::shared_ptr<detail::interactive_actor> > interactive_queue;
	std::vector<std::shared_ptr<detail::standard_actor>    > standard_queue;
	std::vector<std::shared_ptr<detail::graphical_actor>   > graphical_queue;
	std::vector<std::pair<bool, std::function<void()> > > event_queue;

	std::shared_ptr< platform::backend::interface::video::renderer> renderer;
	std::map<std::string, bool> conditions;

	std::map<std::string, std::shared_ptr<cw::simulation::model> > model_list;

protected:
/*	platform::generic::application* application;	*/

};// class stage