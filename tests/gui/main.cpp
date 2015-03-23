#include <crosswind/engine.hpp>

int main(int argc, char **argv) {

    auto engine = std::make_shared<cw::engine>();

    engine->run();

    return 0;

}