#include <exception>
#include <iostream>

#include "crosswind/engine.hpp"

#include "crosswind/platform/filesystem.hpp"
#include "crosswind/composition/stage.hpp"

#include "crosswind/composition/scene.hpp"

#include "crosswind/composition/core.hpp"
#include "crosswind/graphical/video.hpp"

#include "title.hpp"

int main(int argc, char** argv) {

    auto settings = cw::configuration::settings();
    settings.video.window_title = "Sonic the Hedgehog HD";
    settings.window.resolution = glm::ivec2(1024, 768);

    try {

        
        auto engine = std::make_shared<cw::engine>(settings);

        engine->core->engine = engine;
        engine->core->video->set_window_icon("assets/engine/graphics/window/icon.png");

        auto title_scene = std::make_shared<game::scenes::title>();
        engine->stage->init_scene(title_scene);
        auto camera = engine->stage->create_camera(glm::i32vec2(640, 480));

        title_scene->add_camera("main_camera", camera);
        title_scene->set_camera("main_camera");

        engine->stage->add_scene(title_scene);
        engine->stage->load_scene("title");

        

        //auto green_hill_zone = engine->stage->create_scene<game::scenes::green_hill_zone>();

    /*    engine->stage->add_scene("green_hill_zone", green_hill_zone);
        engine->stage->load_scene("green_hill_zone");
        engine->stage->swap_scene("current", "green_hill_zone");
    */
        engine->run();
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
