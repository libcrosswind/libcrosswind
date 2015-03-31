#include <crosswind/engine.hpp>

#include <scenes/green_hill_zone.hpp>

int main(int argc, char **argv) {

    auto engine = std::make_shared<cw::engine>();
    engine->core->filesystem->add_directory("assets", true);

    auto scene = engine->stage->create_scene<game::scenes::green_hill_zone>();
    scene->set_name("green_hill");

    engine->stage->add_scene(scene);
    engine->stage->load_scene("green_hill");

    engine->run();

    return 0;
}