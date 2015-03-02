#pragma once

#include <memory>

#include <crosswind/platform/sdl/sdl_texture.hpp>

namespace cw{
namespace simulation{
namespace detail{

    class texture_mapping;

}// namespace detail
}// namespace simulation
}// namespace cw


class cw::simulation::detail::texture_mapping{
public:
    std::shared_ptr<cw::platform::sdl::sdl_texture> texture;
};
