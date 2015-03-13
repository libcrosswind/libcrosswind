#pragma once

#include <string>
#include <exception>

#include <SDL2/SDL.h>

#include <crosswind/platform/backend/interface/core/exception.hpp>

namespace cw {
namespace platform{
namespace backend{
namespace sdl{
namespace core{

	class exception;

}// namespace core
}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::sdl::core::exception : public cw::platform::backend::interface::core::exception{
public:
	exception(const std::string& function):
		  cw::platform::backend::interface::core::exception(function + " failed: " + SDL_GetError()){
	}

    virtual ~exception() throw (){

    }


};// class exception

 