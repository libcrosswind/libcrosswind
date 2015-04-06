#pragma once

#include <memory>

#include <crosswind/interface/settings.hpp>
#include <crosswind/implementation/platform/application.hpp>
#include <crosswind/implementation/platform/filesystem.hpp>
#include <crosswind/implementation/platform/input.hpp>
#include <crosswind/implementation/graphical/video.hpp>
#include <crosswind/implementation/sound/mixer.hpp>
#include <crosswind/implementation/simulation/physics.hpp>

namespace cw{
namespace interface{
namespace composition{

	class core;

}// namespace composition
}// namespace interface
}// namespace cw

class cw::interface::composition::core{
public:
	core(interface::settings engine_settings = interface::settings()){

		application = std::make_shared<implementation::platform::application>(engine_settings.application.flags);
        filesystem  = std::make_shared<implementation::platform::filesystem>();

        input       = std::make_shared<implementation::platform::input>();
        video       = std::make_shared<implementation::graphical::video>(engine_settings.window.title,
                                                                         engine_settings.video.window_position,
                                                                         engine_settings.video.window_resolution,
                                                                         engine_settings.video.fps,
                                                                         engine_settings.video.video_flags,
                                                                         engine_settings.video.window_flags,
                                                                         engine_settings.window.resizable);

        mixer       = std::make_shared<implementation::sound::mixer>(engine_settings.audio.frequency,
                                                                     engine_settings.audio.format,
                                                                     engine_settings.audio.channels,
                                                                     engine_settings.audio.chunk_size);

        physics     = std::make_shared<implementation::simulation::physics>(engine_settings.physics.gravity,
                                                                            engine_settings.physics.scale,
                                                                            engine_settings.physics.unit_value);
	}

    std::shared_ptr< interface::platform::application > application;
    std::shared_ptr< interface::platform::filesystem  > filesystem;
    std::shared_ptr< interface::platform::input       >	input;
    std::shared_ptr< interface::graphical::video 	  >	video;
    std::shared_ptr< interface::sound::mixer          > mixer;
    std::shared_ptr< interface::simulation::physics   >	physics;

};// class core