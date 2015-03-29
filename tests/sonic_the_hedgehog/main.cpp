#include <crosswind/engine.hpp>

#include <scenes/green_hill_zone.hpp>

int main(int argc, char **argv) {

    auto engine = std::make_shared<cw::engine>();
    engine->core->filesystem->add_directory("assets", true);

    auto scene = std::make_shared<game::scenes::green_hill_zone>();
    scene->set_name("my_scene");

    engine->stage->add_scene(scene);
    engine->stage->load_scene("my_scene");

    engine->run();

    return 0;
}