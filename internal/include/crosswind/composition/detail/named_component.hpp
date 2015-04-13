#pragma once

#include <string>

namespace cw{
namespace composition{
namespace detail{


class named_component{
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

}// namespace detail
}// namespace composition
}// namespace cw
