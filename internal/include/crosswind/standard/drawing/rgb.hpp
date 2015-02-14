#pragma once

#include <array>
#include <crosswind/core/concurrent/atomical_property.hpp>

namespace cw{
namespace standard{
namespace drawing{

	class rgb;

}// namespace drawing
}// namespace standard
}// namespace cw

class cw::standard::drawing::rgb{
public:
	rgb(){
		r = 255;
		g = 255;
		b = 255;
	}

	std::array<unsigned char, 3> array(){
		
		return { r, g, b } ;
	}

	void store(unsigned char r_component, 
			   unsigned char g_component, 
		   	   unsigned char b_component){

		r = r_component;
		g = g_component;
		b = b_component;

	}

	core::concurrent::atomical_property<unsigned char> r;
	core::concurrent::atomical_property<unsigned char> g;
	core::concurrent::atomical_property<unsigned char> b;

};// class rgb