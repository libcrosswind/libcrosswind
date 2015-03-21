#pragma once

#include <crosswind/platform/backend/interface/engine.hpp>

#include <crosswind/platform/backend/sdl/core/input_listener.hpp>
#include <crosswind/platform/backend/sdl/core/image.hpp>
#include <crosswind/platform/backend/sdl/core/mixer.hpp>
#include <crosswind/platform/backend/sdl/core/nucleus.hpp>
#include <crosswind/platform/backend/sdl/core/window.hpp>


namespace cw{
namespace platform{
namespace backend{
namespace sdl{

	class engine;

}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw


class cw::platform::backend::sdl::engine: public cw::platform::backend::interface::engine{
public:
	engine(const auto& engine_settings, const auto& grapical_settings, const auto& physics_settings){

		nucleus 		= std::make_shared<core::nucleus>	(engine_settings[0]);
		
		image 			= std::make_shared<core::image>		(engine_settings[1]);

		mixer 			= std::make_shared<core::mixer>		(engine_settings[2], 
															 engine_settings[3],
															 engine_settings[4],
															 engine_settings[5]);

        input_listener 	= std::make_shared<core::input_listener>();


        window = std::make_shared< core::window >(std::get<0>(grapical_settings),
									  			  std::get<1>(grapical_settings),
    											  std::get<2>(grapical_settings),
    											  std::get<3>(grapical_settings),
											      std::get<4>(grapical_settings));

        window->set_clear_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        physics = std::make_shared<physics::dynamic_world>(physics_settings[0],
			                                               physics_settings[1],
													  	   physics_settings[2]);

		renderer = std::make_shared<interface::video::renderer>();
	}

private:
	std::shared_ptr<  core::nucleus > nucleus;

};// class engine