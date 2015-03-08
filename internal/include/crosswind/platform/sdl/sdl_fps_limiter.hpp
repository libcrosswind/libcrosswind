#pragma once

#include <chrono>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_fps_limiter;

}// namespace sdl
}// namespace platform
}// namespace cw


class cw::platform::sdl::sdl_fps_limiter {
public:
    sdl_fps_limiter(float screen_fps = 60.00f) : ticks_per_frame(0.00f), delta(0.00f), fps(0.00f){
        set_fps(screen_fps);
        previous_delta = std::chrono::high_resolution_clock::now();
    }

    void set_fps(float fps) {
        ticks_per_frame = (1000.00f / fps);
    }

    void begin() {
        begin_time = std::chrono::high_resolution_clock::now();
    }

    void reset_delta() {
        previous_delta = std::chrono::high_resolution_clock::now();
    }

    float get_delta() {
        auto time_difference = std::chrono::duration_cast<std::chrono::nanoseconds>(begin_time - previous_delta);

        previous_delta = begin_time;

        delta = time_difference.count() / 1'000'000;

        return delta;
    }

    float end() {
        end_time = std::chrono::high_resolution_clock::now();
        auto time_difference = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - begin_time);

        float frame_ticks = time_difference.count() / 1'000'000;

        // if frame finished early
        if (frame_ticks < ticks_per_frame) {
            fps = 1000.00f/ticks_per_frame;
            SDL_Delay(ticks_per_frame - frame_ticks); // wait remaining time
        } else {
            fps = 1000.00f/frame_ticks;
        }

        return fps;
    }


private:
    float ticks_per_frame;
    float delta;
    float fps;

    std::chrono::high_resolution_clock::time_point begin_time;
    std::chrono::high_resolution_clock::time_point end_time;

    std::chrono::high_resolution_clock::time_point previous_delta;
};// class sdl_fps_limiter