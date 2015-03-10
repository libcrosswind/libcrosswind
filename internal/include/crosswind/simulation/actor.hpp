#pragma once

#include <map>
#include <crosswind/simulation/sprite.hpp>
#include <crosswind/physics/detail/rigid_body.hpp>

namespace cw{
namespace simulation{

	class actor;

}// namespace simulation
}// namespace cw

class cw::simulation::actor{
public:
	actor(){

	}


	std::map<std::string, std::shared_ptr<sprite> > sprites;
	std::shared_ptr<physics::detail::rigid_body> rigid_body;
};