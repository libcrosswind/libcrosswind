#include "GL/glew.h"
#include <SDL3/SDL.h>

#include "crosswind/graphical/opengl/window.hpp"
#include "crosswind/platform/exception.hpp"

// remove platform/exception

cw::graphical::opengl::window::window(const std::string& window_title,
							          const glm::i32vec2& window_position,
							          const glm::i32vec2& window_resolution,
							          float window_fps,
							          const unsigned int& flags):
window_resource(SDL_CreateWindow,
       			SDL_DestroyWindow,
   				window_title.c_str(),
       			window_resolution[0], 
       			window_resolution[1],
       			flags){

    position = window_position;
    size = window_resolution;

    set_fps(window_fps);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    context = SDL_GL_CreateContext(this->window_resource.ptr());
    if(context == nullptr){
        std::string error = SDL_GetError();
        throw platform::exception("Could not create gl context " + error);
    }

    glewExperimental = GL_TRUE;


    auto glew_status = glewInit();

    if(glew_status != GLEW_OK){
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

cw::graphical::opengl::window::~window(){
    SDL_GL_DeleteContext(context);
}

void cw::graphical::opengl::window::set_fps(const float& new_fps){
    fps = new_fps;
    ticks_per_frame = (1000.00f / new_fps);
}

float cw::graphical::opengl::window::get_fps(){
    return fps;
}

void cw::graphical::opengl::window::begin_frame(){
    begin_time = std::chrono::high_resolution_clock::now();
}

float cw::graphical::opengl::window::end_frame(){
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

void cw::graphical::opengl::window::set_title(const std::string& new_title){
	title = new_title;
    SDL_SetWindowTitle(this->window_resource.ptr(), title.c_str());
}

std::string cw::graphical::opengl::window::get_title(){
	title = SDL_GetWindowTitle(this->window_resource.ptr());
	return title;
}

void cw::graphical::opengl::window::set_brightness(const float& new_brightness){

//	if (SDL_SetWindowBrightness(this->window_resource.ptr(), new_brightness) != 0)
//		throw platform::exception("SDL_SetWindowBrightness");

}

float cw::graphical::opengl::window::get_brightness(){
//    brightness = SDL_GetWindowBrightness(this->window_resource.ptr());
	
	brightness = 1;
	return 1;
}

void cw::graphical::opengl::window::set_position(const glm::ivec2& new_position){
    SDL_SetWindowPosition(this->window_resource.ptr(), new_position.x, new_position.y);
}

glm::i32vec2 cw::graphical::opengl::window::get_position(){
    SDL_GetWindowPosition(this->window_resource.ptr(), &position.x, &position.y);
    return position;
}

void cw::graphical::opengl::window::set_size(const glm::ivec2& new_size){
    SDL_SetWindowSize(this->window_resource.ptr(), new_size.x, new_size.y);
}

glm::i32vec2 cw::graphical::opengl::window::get_size(){
    SDL_GetWindowSize(this->window_resource.ptr(), &size.x, &size.y);
    return size;
}

void cw::graphical::opengl::window::maximize(){
    SDL_MaximizeWindow(this->window_resource.ptr());
}

void cw::graphical::opengl::window::minimize(){
    SDL_MinimizeWindow(this->window_resource.ptr());
}

void cw::graphical::opengl::window::restore(){
    SDL_RestoreWindow(this->window_resource.ptr());
}

void cw::graphical::opengl::window::raise(){
    SDL_RaiseWindow(this->window_resource.ptr());
}

void cw::graphical::opengl::window::show(){
    SDL_ShowWindow(this->window_resource.ptr());
}

void cw::graphical::opengl::window::hide(){
    SDL_HideWindow(this->window_resource.ptr());
}

void cw::graphical::opengl::window::set_icon(SDL_Surface *surface){
    SDL_SetWindowIcon(this->window_resource.ptr(), surface);
}

void cw::graphical::opengl::window::set_clear_color(const glm::vec4& color){
    glClearColor(color.r, color.g, color.b, color.a);
}

void cw::graphical::opengl::window::clear(){
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void cw::graphical::opengl::window::present(){
    SDL_GL_SwapWindow(this->window_resource.ptr());
}
 
