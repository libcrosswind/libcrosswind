#pragma once 

#include <memory>

#include <crosswind/interface/core.hpp>
#include <crosswind/interface/composition/scene.hpp>

#include <crosswind/implementation/composition/camera.hpp>

namespace game{
namespace zones{

    class green_hill;

}// namespace zones
}// namespace game

class game::zones::green_hill : public cw::interface::composition::scene{
		public:
	green_hill(){

	}
	
public:
    virtual void init(){
	    auto main_camera = std::make_shared<cw::implementation::composition::camera>(core->video->window->get_size());
	    set_camera("main_camera", main_camera);

	    for(auto actor: actors){
		    actor.second->core = core;
		    actor.second->init();
	    }

    }

    virtual void deinit(){

    }

	virtual void update(const float& dt){
		scene::update(dt);



	}

};// class stage                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      