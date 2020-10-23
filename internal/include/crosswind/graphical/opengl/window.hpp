#pragma once

#include <string>
#include <chrono>

#include "glm/glm.hpp"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_opengl.h"

#include "crosswind/modules/functional/resource_property.hpp"

// verify SDL_GLContext forward declaration
// verify SDL_Window forward declaration

namespace cw{
namespace graphical{
namespace opengl{

class window{
public:
	window(const std::string& window_title,
            const glm::i32vec2& window_position,
            const glm::i32vec2& window_resolution,
            float window_fps,
            const unsigned int& flags);

    ~window();

    void set_fps(const float& new_fps);

    float get_fps();

    void begin_frame();

    float end_frame();

    void set_title(const std::string& new_title);

    std::string get_title();

    void set_brightness(const float& new_brightness);

    float get_brightness();

    void set_position(const glm::ivec2& new_position);

    glm::i32vec2 get_position();

    void set_size(const glm::ivec2& new_size);

    glm::i32vec2 get_size();

    void maximize();

    void minimize();

    void restore();

    void raise();

    void show();

    void hide();

    void set_icon(SDL_Surface *surface);

    void set_clear_color(const glm::vec4& color);

    void clear();

    void present();

private:
    std::string title;
    float brightness;
    glm::i32vec2 position;
    glm::i32vec2 size;
    float ticks_per_frame;
    float fps;
    std::chrono::high_resolution_clock::time_point begin_time;
    std::chrono::high_resolution_clock::time_point end_time;
    SDL_GLContext context;
    functional::resource_property<SDL_Window> window_resource;
  
};// class window

}// namespace opengl
}// namespace graphical
}// namespace cw