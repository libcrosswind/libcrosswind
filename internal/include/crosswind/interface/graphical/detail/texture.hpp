#pragma once

#include <cstdint>

namespace cw{
namespace interface{
namespace graphical{
namespace detail{

	class texture;

}// namespace detail
}// namespace graphical
}// namespace interface
}// namespace cw

class cw::interface::graphical::detail::texture{
public:
	texture(const uint32_t& c_id): id(c_id){
	}

public:
	uint32_t id;

};// class texture