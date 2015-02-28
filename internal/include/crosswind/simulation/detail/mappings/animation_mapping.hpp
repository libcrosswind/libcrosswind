#pragma once

#include <vector>
#include <string>

namespace cw{
namespace standard{
namespace simulation{
namespace detail{

class animation_mapping;

}// namespace detail
}// namespace simulation	
}// namespace standard
}// namespace cw

class cw::standard::simulation::detail::animation_mapping{
public:
    animation_mapping(){
        current_frame = 0;
    }

    double duration;
    unsigned int current_frame;
    std::vector<std::string> frames;
};

