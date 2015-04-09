#pragma once

#include <functional>

namespace cw{
namespace interface{
namespace composition{
	
	class logic_component;

}// namespace composition
}// namespace interface
}// namespace cw

class cw::interface::composition::logic_component{
public:
	logic_component(){
		init = [this](){
		
		};

		deinit = [this](){

		};

		logic = [this](const float& delta){

		};
	}


	virtual void construct(const std::function<void()>& f_init,
	               		   const std::function<void()>& f_deinit,
               			   const std::function<void(const float&)>& f_logic){
		init = f_init;
		deinit = f_deinit;
		logic = f_logic;

	}


public:
	std::function<void()> init;
	std::function<void()> deinit;
protected:
	std::function<void(const float&)> logic;
};// class logic_component