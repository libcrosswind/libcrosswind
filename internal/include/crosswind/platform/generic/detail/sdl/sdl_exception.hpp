#pragma once

#include <string>
#include <exception>

#include <SDL2/SDL.h>

namespace cw {
namespace platform{
namespace generic{
namespace detail{
namespace sdl{

	class sdl_exception;

}// namespace sdl
}// namespace detail
}// namespace generic
}// namespace platform
}// namespace cw

class cw::platform::generic::detail::sdl::sdl_exception{
public:
	sdl_exception(const char* function)
		: sdl_function_(function),
		  sdl_error_(SDL_GetError()),
		  what_string(sdl_function_ + " failed: " + sdl_error_) {
	}

	~sdl_exception() noexcept {
	}

	const char* what() const noexcept {
		return what_string.c_str();
	}

	std::string sdl_function() const {
		return sdl_function_;
	}

	std::string sdl_error() const {
		return sdl_error_;
	}

private:
	std::string sdl_function_;
	std::string sdl_error_;
	std::string what_string;    
};

 