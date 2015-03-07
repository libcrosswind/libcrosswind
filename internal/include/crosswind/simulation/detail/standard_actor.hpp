#pragma once

namespace cw{
namespace simulation{
namespace detail{

	class standard_actor;

}// namespace detail
}// namespace simulation
}// namespace cw

class cw::simulation::detail::standard_actor{
public:
	standard_actor(){

        delta_count = 0;

	}

	virtual void update(double delta)= 0;

protected:
    float delta_count;
};// class standard_actor