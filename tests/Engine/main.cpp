#include "crosswind/scripting/interpreter.hpp"

int main(int argc, char **argv) {

    auto interpreter = std::make_shared<cw::scripting::interpreter>();
    interpreter->eval_file("scripts/main.chai");

    return 0;
}

