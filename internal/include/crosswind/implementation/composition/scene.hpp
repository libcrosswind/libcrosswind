#pragma once 

#include <memory>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/scene.hpp>

#include <crosswind/implementation/composition/actor.hpp>
#include <crosswind/implementation/composition/camera.hpp>

namespace cw{
namespace implementation{
namespace composition{

	class scene;

}// namespace composition
}// namespace interface
}// namespace cw

class cw::implementation::composition::scene: public cw::interface::composition::scene{
public:
	scene(){

	}
	
public:
    virtual void init(){
	    cameras["main_camera"] = std::make_shared<camera>(core->video->window->get_size());
	    cameras["current"] = cameras["main_camera"];
    }

    virtual void deinit(){

    }


};// class stage                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      