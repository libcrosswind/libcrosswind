#pragma once

#include <map>
#include <memory>
#include <string>

#include "crosswind/composition/detail/named_component.hpp"
#include "crosswind/composition/detail/spatial_component.hpp"
#include "crosswind/composition/detail/logic_component.hpp"

// forward declarations
namespace cw {

namespace graphical{
namespace object{

    class renderable;

}// namespace object
}// namespace graphical

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

    virtual void update(const float& dt) = 0;

	std::shared_ptr<core> core;

	virtual std::map<std::string, std::shared_ptr<graphical::object::renderable> > get_model_map() = 0;

};// class actor

}// namespace composition
}// namespace cw