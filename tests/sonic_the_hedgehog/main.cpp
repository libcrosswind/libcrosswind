#include <crosswind/engine.hpp>

#include <scenes/title.hpp>
//#include <scenes/green_hill_zone.hpp>

int main(int argc, char **argv) {

    auto engine = std::make_shared<cw::engine>();
    engine->core->filesystem->add_directory("assets", true);

    auto title = engine->stage->create_scene<game::scenes::title>();

    engine->stage->add_scene("title", title);
    engine->stage->load_scene("title");

//    auto green_hill_zone = engine->stage->create_scene<game::scenes::green_hill_zone>();

//    engine->stage->add_scene("green_hill_zone", green_hill_zone);
//    engine->stage->load_scene("green_hill_zone");

    engine->run();

    return 0;
}