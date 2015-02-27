#pragma once

#include <string>
#include <vector> 
#include <utility>

namespace cw{
namespace standard{
namespace simulation{
namespace detail{

    class event_mapping;

}// namespace detail
}// namespace simulation
}// namespace standard
}// namespace cw


class cw::standard::simulation::detail::event_mapping{
public:
    std::string what;
    std::string action;
    std::string which;
    std::vector<std::pair<std::string, int> > parameters;
};// class event_mapping