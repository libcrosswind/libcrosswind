#pragma once

#include <string>
#include <exception>

#include <SDL2/SDL.h>

#include <crosswind/interface/platform/exception.hpp>

namespace cw {
namespace implementation{
namespace platform{

	class exception;

}// namespace platform
}// namespace implementation
}// namespace cw

class cw::implementation::platform::exception : public cw::interface::platform::exception{
public:
	exception(const std::string& function):
		  interface::platform::exception(function + " failed: " + SDL_GetError()){
	}

    virtual ~exception() throw (){

    }


};// class exception

 