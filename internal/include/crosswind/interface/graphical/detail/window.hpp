#pragma once

#include <chrono>
#include <string>

#include <glm/glm.hpp>

namespace cw{
namespace interface{
namespace graphical{
namespace detail{

	class window;

}// namespace detail
}// namespace graphical
}// namespace interface
}// namespace cw

class cw::interface::graphical::detail::window{
public:
    window(){

    }

    virtual ~window(){

    }

    virtual void  set_fps(const float& fps) = 0;
    virtual float get_fps() = 0;

    virtual void  begin_frame() = 0;
    virtual float end_frame() = 0;

    virtual void        set_title(const std::string& new_title) = 0;
    virtual std::string get_title() = 0;

    virtual void  set_brightness(const float& new_brightness)  = 0;
    virtual float get_brightness() = 0;

    virtual void        set_position(const glm::vec2& new_position) = 0;
    virtual glm::i32vec2   get_position() = 0;

    virtual void        set_size(const glm::vec2& new_size) = 0;
    virtual glm::i32vec2   get_size() = 0;

    virtual void maximize() = 0;
    virtual void minimize() = 0;
    virtual void restore() = 0;
    virtual void raise() = 0;

    virtual void show() = 0;
    virtual void hide() = 0;

    virtual void set_icon(SDL_Surface *surface) = 0;

    virtual void set_clear_color(const glm::vec4& color) = 0;
    virtual void clear() = 0;
    virtual void present() = 0;

protected:
    std::string title;
    float brightness;
    glm::i32vec2 position;
    glm::i32vec2 size;

    float ticks_per_frame;
    float fps;

    std::chrono::high_resolution_clock::time_point begin_time;
    std::chrono::high_resolution_clock::time_point end_time;


};// class window
