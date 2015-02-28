#pragma once

#include <array>
#include <crosswind/core/concurrent/atomic_property.hpp>

namespace cw{
namespace drawing{

	class rgba;

}// namespace drawing
}// namespace cw

class cw::drawing::rgba{
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

	concurrent::atomic_property<unsigned char> r;
	concurrent::atomic_property<unsigned char> g;
	concurrent::atomic_property<unsigned char> b;
	concurrent::atomic_property<unsigned char> a;

};// class rgba