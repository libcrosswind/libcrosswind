#pragma once

#include <memory>

#include <crosswind/standard/drawing/sdl_texture.hpp>

namespace cw{
namespace standard{
namespace simulation{
namespace detail{

    class texture_mapping;

}// namespace detail
}// namespace simulation
}// namespace standard
}// namespace cw


class cw::standard::simulation::detail::texture_mapping{
public:
    std::shared_ptr<cw::standard::drawing::sdl_texture> texture;
};
