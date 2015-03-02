#pragma once

#include <memory>
#include <string>
#include <vector>

#include <crosswind/geometry/rectangle.hpp>

namespace cw{
namespace simulation{
namespace detail{

    class sprite_mapping;

}// namespace detail
}// namespace simulation
}// namespace cw



class cw::simulation::detail::sprite_mapping{
public:
    std::string name;
    std::shared_ptr<cw::geometry::rectangle<int> > clip;
};// class sprite_mapping