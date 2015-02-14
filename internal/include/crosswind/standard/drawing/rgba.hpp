#pragma once

#include <array>
#include <crosswind/core/concurrent/atomical_property.hpp>

namespace cw{
namespace standard{
namespace drawing{

	class rgba;

}// namespace drawing
}// namespace standard
}// namespace cw

class cw::standard::drawing::rgba{
public:
	rgb(){
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	std::array<unsigned char, 4> array(){
		return {r, g, b, a};
	}

	void store(unsigned char r_component, 
			   unsigned char g_component, 
		   	   unsigned char b_component,
		   	   unsigned char a_component){

		r = r_component;
		g = g_component;
		b = b_component;
		a = a_component;

	}

	core::concurrent::atomical_property<unsigned char> r;
	core::concurrent::atomical_property<unsigned char> g;
	core::concurrent::atomical_property<unsigned char> b;
	core::concurrent::atomical_property<unsigned char> a;

};// class rgba