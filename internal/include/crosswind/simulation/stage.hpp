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

	void setup(std::shared_ptr<platform::backend::interface::engine> engine){

		camera_list["main_camera"] = std::make_shared<camera>(engine->window->size.get());
		camera_list["current"] = camera_list["main_camera"];

		renderer = engine->renderer;

		add(camera_list["current"]);
	//	add(renderer);

	}

	void handle_input(std::shared_ptr<platform::backend::interface::core::input_listener> input_listener) {
		for(auto& i : interactive_queue){
			i->handle_input(input_listener);
		}
	}

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

	virtual void detect_collisions(){
		//1
	/*	int numManifolds = _world->getDispatcher()->getNumManifolds();
		for (int i=0;i<numManifolds;i++)
		{
			//2
			btPersistentManifold* contactManifold =  _world->getDispatcher()->getManifoldByIndexInternal(i);

			//3
			int numContacts = contactManifold->getNumContacts();
			if (numContacts > 0)
			{
				//4
				[[RWDirector sharedInstance] playPopEffect];

				//5
				const btCollisionObject* obA = contactManifold->getBody0();
				const btCollisionObject* obB = contactManifold->getBody1();

				//6
				PNode* pnA = (__bridge PNode*)obA->getUserPointer();
				PNode* pnB = (__bridge PNode*)obB->getUserPointer();

				//7
				if (pnA.tag == kBrickTag) {
					[self destroyBrickAndCheckVictory:pnA];
				}

				//8
				if (pnB.tag == kBrickTag){
					[self destroyBrickAndCheckVictory:pnB];
				}
			}
		}*/
	}

	virtual void render(){

        renderer->begin();

        renderer->set_uniform_matrix("projection_matrix", camera_list["current"]->get_camera_matrix());

        for(auto& model_mapping : model_list){
	        renderer->upload(model_mapping.second);
        }

		renderer->draw();

        renderer->end();

	}

	virtual void draw(){

		for(auto& element: graphical_queue){
           element->draw();
        }

	}


	void add(const std::string& name, std::shared_ptr<model> m){
		model_list[name] = m;
		add(m);
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

	auto get_camera(const std::string& name){
		return camera_list[name];
	}


protected:
	std::vector<std::shared_ptr<detail::interactive_actor> > interactive_queue;
	std::vector<std::shared_ptr<detail::standard_actor>    > standard_queue;
	std::vector<std::shared_ptr<detail::graphical_actor>   > graphical_queue;

	std::vector<std::pair<bool, std::function<void()> > > event_queue;

	std::shared_ptr< platform::backend::interface::video::renderer> renderer;
	//std::shared_ptr< physics::dynamic_world> physics;
	std::map<std::string, bool> conditions;

	std::map<std::string, std::shared_ptr<model> >  model_list;
	std::map<std::string, std::shared_ptr<camera> > camera_list;

};// class stage