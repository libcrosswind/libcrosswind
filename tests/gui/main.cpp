#include <crosswind/engine.hpp>

#include <crosswind/implementation/composition/scene.hpp>
#include <crosswind/implementation/composition/actor.hpp>
#include <crosswind/implementation/composition/camera.hpp>


int main(int argc, char **argv) {

    auto engine = std::make_shared<cw::engine>();

    auto scene = std::make_shared<cw::implementation::composition::scene>();
    scene->set_name("my_scene");

    engine->stage->add_scene(scene);
    engine->stage->swap_scene("current", "my_scene");
    engine->run();

    return 0;

}