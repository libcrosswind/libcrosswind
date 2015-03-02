#pragma once

#include <algorithm>
#include <crosswind/geometry/point.hpp>
#include <crosswind/concurrent/mutex_property.hpp>
#include <crosswind/concurrent/hollow_property.hpp>

namespace cw {
namespace geometry{

	template<class T>
	class rectangle;

}// namespace geometry
}// namespace cw

template<class T>
class cw::geometry::rectangle{
public:	
	rectangle(const auto& nx, const auto& ny, const auto& nw, const auto& nh):
		position(point<T>(nx, ny)), size(point<T>(nw, nh)){

		right_bound.set = [this](const auto& value){
			auto& pos = this->position.acquire();
			auto& dim = this->size.acquire();

			dim.x = value - pos.x + 1;

			this->position.release();
			this->size.release();
		};

		right_bound.get = [this](){
			T result;
			auto& pos = this->position.acquire();
			auto& dim = this->size.acquire();

			result = pos.x + dim.x - 1;

			this->position.release();
			this->size.release();

			return result;
		};

		bottom_bound.set = [this](const auto& value){
			auto& pos = this->position.acquire();
			auto& dim = this->size.acquire();

			dim.y = value - pos.y + 1;

			this->position.release();
			this->size.release();

		};

		bottom_bound.get = [this](){
			T result;
			auto& pos = this->position.acquire();
			auto& dim = this->size.acquire();

			result = pos.y + dim.y - 1;

			this->position.release();
			this->size.release();

			return result;
		};
 
	}

	auto contains_x (const T& x_value) { return x_value >= position.get().x && x_value <= position.get().x + size.get().x; 	}
	auto contains_y (const T& y_value) { return y_value >= position.get().y && y_value <= position.get().y + size.get().y; }
	auto contains_xy(const T& x_value, const T& y_value){ return contains_x(x_value) && contains_y(y_value); }


	auto operator==(const auto& other) const {
		bool result;

		auto& this_pos = position.acquire();
		auto& this_dim = size.acquire();

		auto& other_pos = other.position.acquire();
		auto& other_dim = other.size.acquire();

		result = 	this_pos.x == other_pos.x &&
					this_pos.y == other_pos.y &&
					this_dim.x == other_dim.x &&
					this_dim.y == other_dim.y;

		other.position.release();
		other.size.release();

		size.release();
		position.release();

		return result;
	}

	auto operator!=(const auto& other) const {
		return !(*this == other);
	}


	auto operator+(const auto& offset) const {
		auto& pos = position.acquire();
		auto& dim = size.acquire();

	    rectangle<T> result(pos.x + offset.x, pos.y + offset.y, dim.x, dim.y);

	    size.release();
	    position.release();

	    return result;
	}

	auto operator+=(const auto& offset) {
		auto& pos = position.acquire();

		pos += offset;

		position.release();

		return *this;
	}

	auto operator-(const auto& offset) const {
		auto& pos = position.acquire();
		auto& dim = size.acquire();

	    rectangle<T> result(pos.x - offset.x, pos.y - offset.y, dim.x, dim.y);

	    size.release();
	    position.release();

	    return result;
	}

	auto& operator-=(const auto& offset) {
		auto& pos = position.acquire();
		pos -= offset;
		position.release();

		return *this;
	}
	
	concurrent::mutex_property<point<T> > position;
	concurrent::mutex_property<point<T> > size;
	concurrent::hollow_property<T> right_bound;
	concurrent::hollow_property<T> bottom_bound;
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const cw::geometry::rectangle<T>& rect) {
	auto& pos = rect.position.acquire();
	auto& dim = rect.size.acquire();


	stream << "[x:" << pos.x << ",y:" << pos.y << ",w:" << dim.w << ",h:" << dim.h << "]";

	rect.size.release();
	rect.position.release();

	return stream;
}
