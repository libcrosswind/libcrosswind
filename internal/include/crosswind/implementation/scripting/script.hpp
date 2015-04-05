#pragma once

#include <string>

namespace cw{
namespace implementation{
namespace scripting{

	class script;

}// namespace scripting
}// namespace implementation
}// namespace cw

class cw::implementation::scripting::script{
	virtual std::string get_script() = 0;
};// class script
