#pragma once

#include <string>

namespace cw{
namespace interface{
namespace composition{
	
	class named_component;

}// namespace composition
}// namespace interface
}// namespace cw

class cw::interface::composition::named_component{
public:
	named_component(): name("undefined"){

	}

	virtual void set_name(const std::string& f_name){
		name = f_name;
	}

	virtual std::string& get_name(){
		return name;
	}


protected:
	std::string name;
};// class named_component