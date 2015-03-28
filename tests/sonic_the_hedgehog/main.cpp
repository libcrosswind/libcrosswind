#include <crosswind/engine.hpp>

#include <characters/sonic.hpp>
#include <characters/chunk.hpp>
#include <scenes/green_hill_zone.hpp>

int main(int argc, char **argv) {

    auto engine = std::make_shared<cw::engine>();
    engine->core->filesystem->add_directory("assets", true);

    auto scene = std::make_shared<game::scenes::green_hill_zone>();
    auto actor = std::make_shared<game::characters::sonic>();

    std::vector<std::string> templates = {
        "ground.json"
    };

    std::vector<glm::vec3> positions{
        glm::vec3(0.0f, 0.0f, 0.0f)
    };

    std::vector<glm::vec3> sizes{
        glm::vec3(40.0f, 42.0f, 0.0f)
    };

    auto ground = std::make_shared<game::characters::chunk>(templates, positions, sizes);

    scene->set_name("my_scene");
    scene->add_actor("default", actor);
    scene->add_actor("ground", ground);

    engine->stage->add_scene(scene);
    engine->stage->load_scene("my_scene");

    engine->run();

    return 0;
}