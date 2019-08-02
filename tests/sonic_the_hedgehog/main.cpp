#include "crosswind/engine.hpp"

#include "scenes/title.hpp"
#include "scenes/green_hill_zone.hpp"

int main(int argc, char **argv) {

    auto settings = cw::interface::settings();
    settings.video.window_title = "Sonic the Hedgehog HD";

    auto engine = std::make_shared<cw::engine>(settings);
    engine->core->filesystem->add_directory("assets", true);
    engine->core->video->set_window_icon(engine->core->filesystem->get_file_path("sonic_icon.png"));

    auto title = engine->stage->create_scene<game::scenes::title>();

    engine->stage->add_scene("title", title);
    engine->stage->load_scene("title");

    auto green_hill_zone = engine->stage->create_scene<game::scenes::green_hill_zone>();

/*    engine->stage->add_scene("green_hill_zone", green_hill_zone);
    engine->stage->load_scene("green_hill_zone");
    engine->stage->swap_scene("current", "green_hill_zone");
*/
    engine->run();

    return 0;
}
