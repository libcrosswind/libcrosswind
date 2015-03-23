#pragma once 

#include <memory>

#include <crosswind/engine.hpp>

namespace cw{
namespace interface{
namespace composition{

	class scene;

}// namespace composition
}// namespace interface
}// namespace cw

class cw::interface::composition::scene{
	typedef std::map<std::string, std::shared_ptr<actor> > actor_map;
	typedef std::map<std::string, std::shared_ptr<camera> > camera_map;
public:
	scene(){

	}

protected:
	virtual void handle_events(){
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
	
public:

    virtual void init(std::shared_ptr<engine> engine) = 0;
    virtual void deinit(std::shared_ptr<engine> engine) = 0;

	void setup(std::shared_ptr<cw::engine> engine){

/*		camera_list["main_camera"] = std::make_shared<camera>(engine->window->size.get());
		camera_list["current"] = camera_list["main_camera"];

		add(camera_list["current"]);
*/
	}

	virtual void update(double delta){
		handle_events();

		for(auto& camera: cameras){
           camera.second->update(delta);
        }

		for(auto& actor: actors){
           actor.second->update(delta);
        }
	}



	void post_event(const std::function<void()>& event, const bool& continuous = false){
		event_queue.push_back(std::make_pair(continuous, event));
	}

	virtual void set_actor_map(const actor_map& new_actor_map){
		actors = new_actor_map;
	}

	virtual actor_map& get_actor_map(){
		return actors;
	}

	virtual void set_actor(const std::string& actor_name, std::shared_ptr<actor> actor){
		actors[actor_name] = actor;
	}

	virtual std::shared_ptr<actor> get_actor(const std::string& actor_name){
		return actors[actor_name];
	}

	virtual void set_camera_map(const camera_map& new_camera_map){
		cameras = new_camera_map;
	}

	virtual camera_map& get_camera_map(){
		return cameras;
	}

	virtual void set_camera(const std::string& camera_name, std::shared_ptr<camera> camera){
		cameras[camera_name] = camera;
	}

	virtual std::shared_ptr<camera> get_camera(const std::string& camera_name){
		return camera_list[name];
	}

	virtual void set_name(const std::string& new_name){ name = new_name; }
	virtual std::string get_name(){ return name; }




/*
	virtual void handle_collisions(){
		//1
		int numManifolds = _world->getDispatcher()->getNumManifolds();
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
		}
	}
*/

protected:
    std::string name;
	actor_map actors;
	camera_map cameras;
	std::vector<std::pair<bool, std::function<void()> > > event_queue;

	//std::vector<std::pair<std::function<void()> > > continuous_event_queue;
	//std::vector<std::pair<std::function<void()> > > unique_event_queue;


	//std::shared_ptr< physics::dynamic_world> physics;




};// class stage