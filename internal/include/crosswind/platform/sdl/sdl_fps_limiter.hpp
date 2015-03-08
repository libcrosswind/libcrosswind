#pragma once

#include <chrono>

#include <SDL2/SDL_timer.h>

namespace cw{
namespace platform{
namespace sdl{

	class sdl_fps_limiter;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_fps_limiter{
public:
	sdl_fps_limiter(int screen_fps = 60): ticks_per_frame(0){
		set_fps(60);
        previous_delta = std::chrono::high_resolution_clock::now();
	}

	void set_fps(int fps){
		ticks_per_frame = (1000/fps);
	}

	void begin(){
        begin_time = std::chrono::high_resolution_clock::now();
	}

	void reset_delta(){
		previous_delta = std::chrono::high_resolution_clock::now();
	}

    float get_delta() {

        current_delta = std::chrono::high_resolution_clock::now();
        
        auto time_diference = 
        std::chrono::duration_cast<std::chrono::nanoseconds>(current_delta - previous_delta);

        float delta = time_diference.count();

        delta /= 1000000000;
        previous_delta = current_delta;

        return delta;
    }

	float end(){
  		end_time = std::chrono::high_resolution_clock::now();

        auto time_diference = 
        std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - begin_time);

        float frame_ticks = time_diference.count();

        frame_ticks /= 1000000000;

        //If frame finished early
        if( frame_ticks < ticks_per_frame )
        {
            //Wait remaining time
            SDL_Delay( ticks_per_frame - frame_ticks );
        }

        return frame_ticks;
	}



private:
	int ticks_per_frame;
    std::chrono::high_resolution_clock::time_point begin_time;
    std::chrono::high_resolution_clock::time_point end_time;

    std::chrono::high_resolution_clock::time_point previous_delta;
    std::chrono::high_resolution_clock::time_point current_delta;
};