#pragma once

#include <functional>

namespace cw{
namespace core{
namespace concurrent{
namespace detail{

	template<class T>
	property;

}// detail
}// namespace concurrent
}// namespace core
}// namespace cw


template<class T>
class cw::core::concurrent::detail::property{
public:
	std::function<void(T)> set;
	std::function<T(void)> get;
};//class atomical_property
