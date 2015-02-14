#include <Crosswind/concurrency/mutexed_property.hpp>
#include <Crosswind/graphics/color/rgb.hpp>

#include <string>

namespace cw{
	namespace gui{
			namespace detail{
				class text{
				public:
					mutexed_property<std::string> value;
					rgb color;
				}; //class text
			} //namespace detail
	} //namespace gui
} //namespace cw