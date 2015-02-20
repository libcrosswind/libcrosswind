#pragma once

#include <iostream>
#include <SDL2/SDL_point.h>

//#include <crosswind/core/concurrent/atomical_property.hpp>

namespace cw {
namespace standard{
namespace geometry{

	template<class T>
	class point;

}// namespace geometry
}// namespace standard
}// namespace cw

template<class T>
class cw::standard::geometry::point : public SDL_Point {
public:
	point() {
		x = 0;
		y = 0;
	}

	point(T nx, T ny) {
		x = nx;
		y = ny;
	}

	bool operator==(const auto& other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const auto& other) const {
		return !(*this == other);
	}

	auto operator+(const auto& other) const {
		return point<T>(x + other.x, y + other.y);
	}

	auto& operator+=(const auto& other) {

		x += other.x;
		y += other.y;

		return *this;
	}

	auto operator-(const auto& other) const {
		return point(x - other.x, y - other.y);
	}

	auto& operator-=(const auto& other) {
		x -= other.x;
		y -= other.y;

		return *this;
	}	

	auto operator/(auto value) const {
		return point(x / value, y / value);
	}
	
	auto& operator/=(auto value) {
		x /= value;
		y /= value;

		return *this;
	}	

	auto operator*(auto value) const {
		return point(x * value, y * value);
	}

	auto& operator*=(auto value) {
		x *= value;
		y *= value;

		return *this;
	}

	T x;
	T y;

//	core::concurrent::atomical_property<T> x;
//	core::concurrent::atomical_property<T> y;
};

std::ostream& operator<<(std::ostream& stream, const cw::standard::geometry::point& p) {
	stream << "[x:" << p.x << ",y:" << p.y << "]";
	return stream;
}