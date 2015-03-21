#pragma once

#include <memory>

#include <crosswind/backend/interface/input.hpp>
#include <crosswind/backend/interface/image.hpp>
#include <crosswind/backend/interface/mixer.hpp>
#include <crosswind/backend/interface/physics.hpp>

namespace cw{
    
    class engine;

}// namespace cw

class cw::engine{
public:
	engine(){
		
	}

public:
    std::shared_ptr<  backend::interface::graphical > 	graphical;
    std::shared_ptr<  backend::interface::audio >  	  	audio;
    std::shared_ptr<  backend::interface::input > 		input;
    std::shared_ptr<  backend::interface::physics> 		physics;
    
};// class engine