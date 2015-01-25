#pragma once

#include <Crosswind/events/delegate.hpp>

namespace cw{
	class input_listener{
	public:
        delegate<int, int>			on_mouse_up;
        delegate<int, int>          on_mouse_move;
		delegate<int, int, int>     on_mouse_down;

        delegate<int> on_key_down;
        delegate<int> on_key_up;

	};
}