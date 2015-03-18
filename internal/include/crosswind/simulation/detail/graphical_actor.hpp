#pragma once

#include <memory>

namespace cw{
namespace simulation{
namespace detail{

	class graphical_actor;

}// namespace detail
}// namespace simulation
}// namespace cw

class cw::simulation::detail::graphical_actor{
public:
	graphical_actor(){

	}

	virtual void draw() = 0;

};// class graphical_actor
