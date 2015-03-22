#include <crosswind/engine.hpp>


int main(int argc, char **argv) {

    /*
    auto window_settings   = glm::vec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    auto default_resolution = glm::vec2(320.0f, 224.0f);
    auto window_resolution = glm::vec2(640.0f, 480.0f);
*/

    auto engine = std::make_shared<cw::engine>();

    engine->run();

    return 0;
}