#pragma once

#include <map>
#include <Crosswind/events/delegate.hpp>

namespace cw{
	class gui_element{
	public:


        std::map<std::string, delegate<void> > actions;

	};
}