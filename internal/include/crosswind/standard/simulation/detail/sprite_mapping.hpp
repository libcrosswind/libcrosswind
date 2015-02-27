#pragma once

#include <memory>
#include <string>
#include <vector>

namespace cw{
namespace standard{
namespace simulation{
namespace detail{

    class sprite_mapping;

}// namespace detail
}// namespace simulation
}// namespace standard
}// namespace cw



class cw::standard::simulation::detail::sprite_mapping{
public:
    std::string name;
    std::shared_ptr<cw::standard::geometry::rectangle<int> > clip;
};// class sprite_mapping