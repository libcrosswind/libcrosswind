#pragma once

#include <iostream>
#include <SDL2/SDL_point.h>

#include <crosswind/standard/geometry/rectangle.hpp>
#include <crosswind/core/concurrent/atomical_property.hpp>

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

	point(const SDL_Point& point) {
		x = point.x;
		y = point.y;
	}

	point(T nx, T ny) {
		x = nx;
		y = ny;
	}

	template<typename U>
	bool operator==(const point<T>& other) const {
		return x == other.x && y == other.y;
	}

	template<typename U>
	bool operator!=(const point<T>& other) const {
		return !(*this == other);
	}

	template<typename U>
	point<T> operator+(const point<U>& other) const {
		return point<T>(x + other.x, y + other.y);
	}

	template<typename U>
	point<T> operator-(const point<U>& other) const {
		return point(x - other.x, y - other.y);
	}

	point<T> operator/(auto value) const {
		return point(x / value, y / value);
	}

	point<T> operator*(auto value) const {
		return point(x * value, y * value);
	}

	template<typename U>
	point<T>& operator+=(const point<U>& other) {
		x += other.x;
		y += other.y;

		return *this;
	}

	template<typename U>
	point<T>& operator-=(const point<U>& other) {
		x -= other.x;
		y -= other.y;

		return *this;
	}

	point<T>& operator/=(auto value) {
		x /= value;
		y /= value;

		return *this;
	}

	point<T>& operator*=(auto value) {
		x *= value;
		y *= value;

		return *this;
	}

	core::concurrent::atomical_property<T> x;
	core::concurrent::atomical_property<T> y;
};

std::ostream& operator<<(std::ostream& stream, const cw::standard::geometry::point& p) {
	stream << "[x:" << p.x << ",y:" << p.y << "]";
	return stream;
}