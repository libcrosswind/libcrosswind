#pragma once

#include <iostream>

//#include <crosswind/core/concurrent/atomical_property.hpp>

namespace cw {
namespace geometry{

	template<class T>
	class point;

}// namespace geometry
}// namespace cw

template<class T>
class cw::geometry::point {
public:
	point() {
		x = 0;
		y = 0;
	}

	point(const T& nx, const T& ny) {
		x = nx;
		y = ny;
	}

    point(const point<T>& other){
        x = other.x;
        y = other.y;
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

//	concurrent::atomical_property<T> x;
//	concurrent::atomical_property<T> y;
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const cw::geometry::point<T>& p) {
	stream << "[x:" << p.x << ",y:" << p.y << "]";
	return stream;
}