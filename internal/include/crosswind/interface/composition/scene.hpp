#pragma once 

#include <memory>
#include <stdexcept>

#include <crosswind/interface/core.hpp>

#include <crosswind/interface/composition/actor.hpp>
#include <crosswind/interface/composition/camera.hpp>

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

    virtual void init()   = 0;
    virtual void deinit() = 0;

	virtual void update(const float& delta){
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

	virtual void add_actor(const std::string& actor_name, std::shared_ptr<actor> actor){
		actors[actor_name] = actor;
	}

	virtual std::shared_ptr<actor> get_actor(const std::string& actor_name){

		if(actors.find(actor_name) != actors.end()){
			return actors[actor_name];
		} else {
			throw std::runtime_error("Could not find: " + actor_name);
		}

	}

	virtual void set_camera_map(const camera_map& new_camera_map){
		cameras = new_camera_map;
	}

	virtual camera_map& get_camera_map(){
		return cameras;
	}

	virtual void set_camera(const std::string& camera_name, std::shared_ptr<camera> camera){
		if(cameras.empty()){
			cameras["current"] = camera;
		}
		cameras[camera_name] = camera;
	}

	virtual std::shared_ptr<camera> get_camera(const std::string& camera_name){

		if(cameras.find(camera_name) != cameras.end()){
			return cameras[camera_name];
		} else {
			throw std::runtime_error("Could not find: " + camera_name);
		}

	}

	virtual void set_name(const std::string& new_name){ name = new_name; }
	virtual std::string get_name(){ return name; }


	virtual void handle_collisions(){
		//1
		int numManifolds = core->physics->get_collision_manifolds_number();
		for (int i=0;i<numManifolds;i++)
		{
			//2
			btPersistentManifold* contactManifold = core->physics->get_manifold_by_index(i);

			//3
			int numContacts = contactManifold->getNumContacts();
			if (numContacts > 0)
			{
				//4
//				[[RWDirector sharedInstance] playPopEffect];

				//5
				const btCollisionObject* obA = contactManifold->getBody0();
				const btCollisionObject* obB = contactManifold->getBody1();

/*				//6
				PNode* pnA = (__bridge PNode*)obA->getUserPointer();
				PNode* pnB = (__bridge PNode*)obB->getUserPointer();

				//7
				if (pnA.tag == kBrickTag) {
					[self destroyBrickAndCheckVictory:pnA];
				}

				//8
				if (pnB.tag == kBrickTag){
					[self destroyBrickAndCheckVictory:pnB];
				}*/
			}
		}
	}


	std::shared_ptr<core> core;

protected:
    std::string name;
	actor_map actors;

	camera_map cameras;
	std::vector<std::pair<bool, std::function<void()> > > event_queue;

	//std::vector<std::pair<std::function<void()> > > continuous_event_queue;
	//std::vector<std::pair<std::function<void()> > > unique_event_queue;


	//std::shared_ptr< physics::dynamic_world> physics;




};// class stage