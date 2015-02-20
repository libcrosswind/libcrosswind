#pragma once

#include <algorithm>
#include <SDL2/SDL_rect.h>

#include <crosswind/standard/geometry/point.hpp>

namespace cw {
namespace standard{
namespace geometry{

	template<class T>
	rectangle;

}// namespace geometry
}// namespace standard
}// namespace cw

template<class T>
class cw::standard::geometry::rectangle: public SDL_Rect{
public:	
	rectangle(auto nx, auto ny, auto nw, auto nh): 		
		position(nx, ny), size(nw, nh){

		right_bound.set = [](const auto& value){
			auto& pos = position.acquire();
			auto& dim = size.acquire();

			dim.x = value - pos.x + 1;

			position.release();
			size.release();
		};

		right_bound.get = [](){
			T result;
			auto& pos = position.acquire();
			auto& dim = size.acquire();

			result = value - pos.x + dim.x - 1;

			position.release();
			size.release();

			return result;
		};

		bottom_bound.set = [](const auto& value){
			auto& pos = position.acquire();
			auto& dim = size.acquire();

			dim.y = value - pos.y + 1;

			position.release();
			size.release();

		};

		bottom_bound.get = [](){
			T result;
			auto& pos = position.acquire();
			auto& dim = size.acquire();

			result = value - pos.y + dim.y - 1;

			position.release();
			size.release();

			return result;
		};
 
	}

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
	
	core::concurrent::mutexed_property<point<T> > position;
	core::concurrent::mutexed_property<point<T> > size;
	core::concurrent::hollow_property<T> right_bound;
	core::concurrent::hollow_property<T> bottom_bound;
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const cw::standard::geometry::rectangle<T>& rect) {
	auto& pos = rect.position.acquire();
	auto& dim = rect.size.acquire();


	stream << "[x:" << pos.x << ",y:" << pos.y << ",w:" << dim.w << ",h:" << dim.h << "]";

	rect.size.release();
	rect.position.release();

	return stream;
}
