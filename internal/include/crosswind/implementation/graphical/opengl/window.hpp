#pragma once

#include <string>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>

#include <glm/glm.hpp>

#include <crosswind/modules/functional/resource_property.hpp>
#include <crosswind/implementation/platform/exception.hpp>

namespace cw{
namespace implementation{
namespace graphical{
namespace opengl{

	class window;

}// namespace opengl
}// namespace graphical
}// namespace implementation
}// namespace cw

class cw::implementation::graphical::opengl::window: public cw::interface::graphical::detail::window{
public:
	window(const std::string& window_title,
            const glm::i32vec2& window_position,
            const glm::i32vec2& window_resolution,
            float window_fps,
            const unsigned int& flags):
            window_resource(SDL_CreateWindow,
                   SDL_DestroyWindow,
                   window_title.c_str(),
                   window_position[0], window_position[1], window_resolution[0], window_resolution[1],
                   flags){

        set_fps(window_fps);

        context = SDL_GL_CreateContext(this->window_resource.ptr());
        if(context == nullptr){
            std::string error = SDL_GetError();
            throw platform::exception("Could not create gl context " + error);
        }

        if(glewInit() != GLEW_OK){
            throw platform::exception("Could not initialize glew");
        }

        printf("OpenGL version: %s \n", glGetString(GL_VERSION));

        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

        //Vsync
        SDL_GL_SetSwapInterval(1);//Vsync may drop one or two frames per second but avoids screen tearing.

        set_clear_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    virtual ~window(){
        SDL_GL_DeleteContext(context);
    }

    virtual void  set_fps(const float& new_fps){
        fps = new_fps;
        ticks_per_frame = (1000.00f / new_fps);
    }

    virtual float get_fps(){
        return fps;
    }

    virtual void  begin_frame(){
        begin_time = std::chrono::high_resolution_clock::now();
    }

    virtual float end_frame(){
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

    virtual void set_title(const std::string& new_title){
    	title = new_title;
        SDL_SetWindowTitle(this->window_resource.ptr(), title.c_str());
    }

    virtual std::string get_title(){
		title = SDL_GetWindowTitle(this->window_resource.ptr());
		return title;
    }

    virtual void  set_brightness(const float& new_brightness){

		if (SDL_SetWindowBrightness(this->window_resource.ptr(), new_brightness) != 0)
			throw platform::exception("SDL_SetWindowBrightness");

    }

    virtual float get_brightness(){
        brightness = SDL_GetWindowBrightness(this->window_resource.ptr());
		return brightness;
	}

    virtual void  set_position(const glm::vec2& new_position){
        SDL_SetWindowPosition(this->window_resource.ptr(), new_position.x, new_position.y);
    }

    virtual glm::vec2   get_position(){
        int x, y;
        SDL_GetWindowPosition(this->window_resource.ptr(), &x, &y);
        position.x = x;
        position.y = y;
        return position;
    }

    virtual void set_size(const glm::vec2& new_size){
        SDL_SetWindowSize(this->window_resource.ptr(), new_size.x, new_size.y);
    }

    virtual glm::vec2 get_size(){
        int w, h;
        SDL_GetWindowSize(this->window_resource.ptr(), &w, &h);
        size.x = w;
        size.y = h;
        return size;
    }

    virtual void maximize(){
        SDL_MaximizeWindow(this->window_resource.ptr());
    }

    virtual void minimize(){
        SDL_MinimizeWindow(this->window_resource.ptr());
    }

    virtual void restore(){
        SDL_RestoreWindow(this->window_resource.ptr());
    }

    virtual void raise(){
        SDL_RaiseWindow(this->window_resource.ptr());
    }

    virtual void show(){
        SDL_ShowWindow(this->window_resource.ptr());
    }

    virtual void hide(){
        SDL_HideWindow(this->window_resource.ptr());
    }

    virtual void set_icon(SDL_Surface *surface){
        SDL_SetWindowIcon(this->window_resource.ptr(), surface);
    }

    virtual void set_clear_color(const glm::vec4& color){
        glClearColor(color.r, color.g, color.b, color.a);
    }

    virtual void clear(){
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    virtual void present(){
        SDL_GL_SwapWindow(this->window_resource.ptr());
    }

private:
    SDL_GLContext context;
    functional::resource_property<SDL_Window> window_resource;
  
};// class window