#pragma once

#include <map>
#include <memory>
#include <string>

#include "crosswind/composition/detail/named_component.hpp"
#include "crosswind/composition/detail/spatial_component.hpp"
#include "crosswind/composition/detail/logic_component.hpp"

// forward declarations
namespace cw {

namespace composition {
	
	class core;

}// namespace composition
}// namespace cw


namespace cw{
namespace composition{

class actor: public detail::named_component,
			 public detail::spatial_component,
			 public detail::logic_component{
	
public:
	actor(const std::string& c_name);
	~actor();


	std::shared_ptr<core> core;

};// class actor

}// namespace composition
}// namespace cw