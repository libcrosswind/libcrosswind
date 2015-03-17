#pragma once

#include <memory>

#include <crosswind/platform/backend/interface/core/input_listener.hpp>
#include <crosswind/platform/backend/interface/core/image.hpp>
#include <crosswind/platform/backend/interface/core/mixer.hpp>
#include <crosswind/platform/backend/interface/core/window.hpp>
#include <crosswind/physics/dynamic_world.hpp>
#include <crosswind/platform/backend/interface/video/renderer.hpp>

//#include <crosswind/platform/backend/interface/physics/dynamic_world.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace interface{

	class engine;

}// namespace interface
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::interface::engine{
protected:
	engine(){

	}

public:
    bool running;
    std::shared_ptr<  core::image >  			image;
    std::shared_ptr<  core::mixer >  			mixer;
    std::shared_ptr<  core::input_listener > 	input_listener;
    std::shared_ptr<  core::window    	> 		window;
    std::shared_ptr<  physics::dynamic_world> 	physics_world;
    std::shared_ptr<  video::renderer   >       renderer;
};// class engine