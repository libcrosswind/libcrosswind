#pragma once

#include <map>
#include <Crosswind/events/delegate.hpp>

namespace cw{
	class gui_element{
	public:

        delegate<>          on_show;
        delegate<>          on_hide;

        std::map<std::string, delegate<> > actions;

	};
}