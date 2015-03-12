#pragma once 

namespace cw{
namespace simulation{

	class resource_manager;

}// namespace simulation
}// namespace cw

class cw::simulation::resource_manager{
public:
	resource_manager(){

	}


	std::shared_ptr<cw::platform::audio::mixer> mixer;
	std::shared_ptr<> 
};