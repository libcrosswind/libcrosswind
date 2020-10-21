#pragma once

#include <memory>

#include "crosswind/configuration/settings.hpp"

// forward declarations
namespace cw{
namespace composition{

    class core;
    class stage;

}// namespace composition
}// namespace cw

namespace cw{

class engine : std::enable_shared_from_this<engine> {
public:
    engine(const configuration::settings& c_settings);

    void run();

    std::shared_ptr<composition::core>  core;
    std::shared_ptr<composition::stage> stage;

private:
    void update();
    void draw();

};// class engine

}// namespace cw
