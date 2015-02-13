#pragma once

#include <Crosswind/concurrency/atomical_property.hpp>
#include <array>

namespace cw{
	namespace graphics{
		namespace color{
			class rgb{
				public:
					rgb(){
						r = 255;
						g = 255;
						b = 255;
					}

					auto array(){
						return std::array<unsigned char, 3>(r, g, b);
					}

					void store(unsigned char r_component, 
							   unsigned char g_component, 
						   	   unsigned char b_component){

						r = r_component;
						g = g_component;
						b = b_component;

					}

					atomical_property<unsigned char> r;
					atomical_property<unsigned char> g;
					atomical_property<unsigned char> b;
			};
		}
	}
}