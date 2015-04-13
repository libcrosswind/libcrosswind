#include <memory>

#include "crosswind/composition/core.hpp"
#include "crosswind/configuration/settings.hpp"
#include "crosswind/platform/application.hpp"
#include "crosswind/platform/filesystem.hpp"
#include "crosswind/platform/input.hpp"
#include "crosswind/graphical/video.hpp"
#include "crosswind/sound/mixer.hpp"
#include "crosswind/simulation/physics.hpp"

cw::composition::core::core(const cw::configuration::settings& engine_settings){

    application = std::make_shared<platform::application>(engine_settings.application.flags);
    filesystem  = std::make_shared<platform::filesystem>();

    input       = std::make_shared<platform::input>();

    video       = std::make_shared<graphical::video>(engine_settings.window.title,
                                                     engine_settings.video.window_position,
                                                     engine_settings.window.resolution,
                                                     engine_settings.video.fps,
                                                     engine_settings.video.video_flags,
                                                     engine_settings.video.window_flags,
                                                     engine_settings.window.resizable);

    mixer       = std::make_shared<sound::mixer>(engine_settings.audio.frequency,
                                                 engine_settings.audio.format,
                                                 engine_settings.audio.channels,
                                                 engine_settings.audio.chunk_size);

    physics     = std::make_shared<simulation::physics>(engine_settings.physics.gravity,
                                                        engine_settings.physics.scale,
                                                        engine_settings.physics.unit_value);
}

  