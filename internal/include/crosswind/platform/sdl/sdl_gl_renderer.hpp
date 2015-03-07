#pragma once

#include <memory>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <crosswind/concurrent/resource_property.hpp>
#include <crosswind/math/clamp.hpp>
#include <crosswind/math/vector3.hpp>
#include <crosswind/platform/sdl/sdl_exception.hpp>


namespace cw{
namespace platform{
namespace sdl{

	class sdl_gl_renderer;

}// namespace sdl
}// namespace platform
}// namespace cw


class cw::platform::sdl::sdl_gl_renderer{
public:
	template<typename... Args>
    sdl_gl_renderer(const std::vector<int>& gl_version, Args... args){

        context = SDL_GL_CreateContext(args...);

        if(context == nullptr){
            throw sdl_exception("Could not create gl context ");
        }

        if(glewInit() != GLEW_OK){
            throw sdl_exception("Could not initialize glew");
        }
        printf("OpenGL version: %s \n", glGetString(GL_VERSION));

        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

        //Vsync
        SDL_GL_SetSwapInterval(1);

	}

    ~sdl_gl_renderer(){
        SDL_GL_DeleteContext(context);
	}


    void set_clear_color(float r, float g, float b, float a = 1.f) {

        cw::math::clamp<float> clamp(0.f, 1.f);

        //Initialize clear color
        glClearColor(clamp(r), clamp(g), clamp(b), clamp(a));
    }


    void clear() {
        //Set the base depth to 1.0
        glClearDepth(1.0);

        //Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

    void present(auto window_ptr) {
        //Update screen
        SDL_GL_SwapWindow( window_ptr );
    }

private:
    SDL_GLContext context;
	//std::unique_ptr<concurrent::resource_property<void> > context;
};// class sdl_gl_renderer