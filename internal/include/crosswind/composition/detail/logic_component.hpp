#pragma once

#include <functional>

namespace cw {
	namespace graphical {
		namespace opengl {
			class renderer;
		}
	}
}


namespace cw{
namespace composition{
namespace detail{

class logic_component{
public:
	logic_component(){
	}

public:
	virtual void draw(std::shared_ptr<cw::graphical::opengl::renderer> renderer) = 0;

protected:
	virtual void init() = 0;
	virtual void deinit() = 0;
	virtual void logic(const float&) = 0;

};// class logic_component

}// namespace detail
}// namespace composition
}// namespace cw

