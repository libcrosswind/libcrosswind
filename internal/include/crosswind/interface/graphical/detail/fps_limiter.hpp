#pragma once

#include <chrono>

namespace cw{
namespace platform{
namespace backend{
namespace interface{
namespace core{

    class fps_limiter;

}// namespace detail
}// namespace graphical
}// namespace interface
}// namespace backend
}// namespace cw


class cw::backend::interface::graphical::detail::fps_limiter {
public:
    fps_limiter(){

    }

    virtual void set_fps(float fps) = 0;

    virtual void begin() = 0;

    virtual void reset_delta() = 0;

    virtual float get_delta() = 0;

    virtual float end() = 0;

};// class fps_limiter