#include <crosswind/engine.hpp>

#include <characters/sonic.hpp>
#include <zones/green_hill.hpp>

int main(int argc, char **argv) {

    auto engine = std::make_shared<cw::engine>();
    engine->core->filesystem->add_directory("assets", true);

    auto scene = std::make_shared<cw::implementation::composition::scene>();
    auto actor = std::make_shared<cw::implementation::composition::actor>();

    scene->set_name("my_scene");

    scene->add_actor("default", actor);

    engine->stage->add_scene(scene);
    engine->stage->load_scene("my_scene");

    engine->run();

    return 0;
}