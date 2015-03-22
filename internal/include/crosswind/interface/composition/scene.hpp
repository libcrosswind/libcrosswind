#pragma once

namespace cw{
namespace interface{
namespace composition{

	class scene;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::interface::composition::scene{
public:
	scene(){
		
	}

	virtual void add_stage(std::shared_ptr<detail::stage> stage) = 0;
	virtual void swap_stage(const std::string& previous_stage, const std::string& new_stage) = 0;
	virtual void remove_stage(const std::string& stage_name) = 0;

	virtual void update(float dt) = 0;

	std::map<std::string, std::shared_ptr<detail::stage> > stages;

};// class scene