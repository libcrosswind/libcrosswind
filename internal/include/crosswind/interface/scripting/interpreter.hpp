#pragma once

namespace cw{
namespace interface{
namespace scripting{
	
	class interpreter;

}// namespace scripting
}// namespace interface
}// namespace cw

class cw::interface::scripting::interpreter{
public:
	interpreter(){

	}

	virtual void parse(const std::string& code) = 0;
	virtual void run() = 0;
}// class interpreter