#pragma once 

#include <memory>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/scene.hpp>

#include <crosswind/implementation/composition/camera.hpp>

namespace cw{
namespace implementation{
namespace composition{

	class scene;

}// namespace composition
}// namespace interface
}// namespace cw

class hedgehog::implementation::composition::green_hill: public cw::interface::composition::scene{
public:
	green_hill(){

	}
	
public:
    virtual void init(){
	    cameras["main_camera"] = std::make_shared<camera>(core->video->window->get_size());
	    cameras["current"] = cameras["main_camera"];

	    for(auto actor: actors){
		    actor.second->core = core;
		    actor.second->init();
	    }
    }

    virtual void deinit(){

    }

};// class stage                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      