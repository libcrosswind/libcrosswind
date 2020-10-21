/*#pragma once

#include <memory>
#include <string>

// forward declarations
namespace chaiscript{

	class ChaiScript;

}// namespace chaiscript

namespace cw{
namespace scripting{

class interpreter{
public:
	interpreter();

	void eval_file(const std::string& filename);

private:
	void bind_datatypes();

	void bind_settings();

	void bind_engine();

	void bind_filesystem();

	void bind_input();

	void bind_video();

	void bind_sound();

	void bind_graphical();

	void bind_composition();

	std::shared_ptr<chaiscript::ChaiScript> chai;

};// class interpreter

}// namespace scripting
}// namespace cw
*/