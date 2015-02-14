#pragma once

#include <crosswind/core/concurrent/atomical_property.hpp>

namespace cw{
namespace standard{
namespace geometry{

	template<class T>
	class rectangle;

}// namespace geometry
}// namespace standard
}// namespace cw

template<class T>
class cw::standard::geometry::rectangle{
public:
	rectangle(T x_value = 0, T y_value = 0, T w_value = 1, T h_value = 1){
		x 		= x_value;
		y		= y_value;
		width  	= w_value;
		height  = h_value;
	}

	//Positioning
	auto contains_x(T x_value) { return x_value >= this->x && x_value <= this->width  + this->x; }

	auto contains_y(T y_value) { return y_value >= this->y && y_value <= this->height + this->y; }

	auto collides_x(T x_value) { return x_value == this->x || x_value == this->x + this->width;  }
	auto collides_y(T y_value) { return y_value == this->y || y_value == this->y + this->get_height; }

	auto intersects_x(T x_value){ return contains_x(x) || collides_x(x); }
	auto intersects_y(T y_value){ return contains_y(y) || collides_y(y); }

	auto contains_xy  (T x_value, T y_value){ return contains_x(x_value)	&& contains_y(y_value);        }
	auto collides_xy  (T x_value, T y_value){ return collides_x(x_value) 	&& collides_y(y_value);        }
	auto intersects_xy(T x_value, T y_value){ return contains_xy(x_value, y_value) || collides_xy(x_value, y_value);    }

	auto contains(rectangle<T>& rect){
		/*
			T other_x = rect.x;
			T other_y = rect.y;
			T other_w = rect.width;
			T other_h = rect.height;
		*/
		return contains_xy(rect.x, rect.y) && contains_xy(rect.x + rect.width, rect.y + rect.height);
	}

    core::concurrent::atomical_property<T> x;
	core::concurrent::atomical_property<T> y;
    core::concurrent::atomical_property<T> width;
	core::concurrent::atomical_property<T> height;
};// class rectangle


