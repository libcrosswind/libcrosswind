#pragma once

#include <string>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>
#include <glm/glm.hpp>

#include <crosswind/concurrent/hollow_property.hpp>
#include <crosswind/concurrent/resource_property.hpp>
#include <crosswind/platform/sdl/sdl_exception.hpp>

namespace cw{
namespace platform{
namespace backend{
namespace sdl{
namespace video{

	class window;

}// namespave video
}// namespace sdl
}// namespace backend
}// namespace platform
}// namespace cw

class cw::platform::backend::sdl::window: public cw::platform::backend::video::window{
public:

	window(const std::string& window_title, const glm::vec4& bounds, float fps, const unsigned int& flags):
            cw::platform::backend::video::window(fps),
            window_resource(SDL_CreateWindow,
                   SDL_DestroyWindow,
                   window_title.c_str(),
                   bounds[0], bounds[1], bounds[2], bounds[3],
                   flags){

		title.set = [this](const std::string& text){
			SDL_SetWindowTitle(this->window_resource.ptr(), title.get().c_str());
		};

		title.get = [this](){
			std::string text;
			text = SDL_GetWindowTitle(this->window_resource.ptr());
			return text;
		};

		brightness.set = [this](const float& bright){
			if (SDL_SetWindowBrightness(this->window_resource.ptr(), brightness) != 0)
				throw sdl_exception("SDL_SetWindowBrightness");
        };

		brightness.get = [this](){
			float bright;
            bright = SDL_GetWindowBrightness(this->window_resource.ptr());
			return bright;
		};

        position.set = [this](const glm::vec2& new_position){
            SDL_SetWindowPosition(this->window_resource.ptr(), new_position.x, new_position.y);
        };

        position.get = [this](){
            int x, y;
            SDL_GetWindowPosition(this->window_resource.ptr(), &x, &y);
            return glm::vec2(x, y);
        };


		size.set = [this](const glm::vec2& new_size){
			SDL_SetWindowSize(this->window_resource.ptr(), new_size.x, new_size.y);
		};

		size.get = [this](){
			int w, h;
			SDL_GetWindowSize(this->window_resource.ptr(), &w, &h);
			return glm::vec2(w, h);
		};

        context = SDL_GL_CreateContext(this->window_resource.ptr());
        if(context == nullptr){
            throw sdl_exception("Could not create gl context ");
        }

        if(glewInit() != GLEW_OK){
            throw sdl_exception("Could not initialize glew");
        }

        printf("OpenGL version: %s \n", glGetString(GL_VERSION));

        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

        //Vsync
        SDL_GL_SetSwapInterval(1);//Vsync may drop one or two frames per second but avoids screen tearing.

        set_clear_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    ~sdl_window(){
        SDL_GL_DeleteContext(context);
    }

    virtual void maximize() {
		SDL_MaximizeWindow(this->window_resource.ptr());
	}

    virtual void minimize() {
		SDL_MinimizeWindow(this->window_resource.ptr());
	}

    virtual void show() {
		SDL_ShowWindow(this->window_resource.ptr());
	}

    virtual void hide() {
		SDL_HideWindow(this->window_resource.ptr());
	}

    virtual void restore() {
		SDL_RestoreWindow(this->window_resource.ptr());
	}

    virtual void raise() {
		SDL_RaiseWindow(this->window_resource.ptr());
	}

    virtual void set_clear_color(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    virtual void clear() {
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    virtual void present() {
        //Update screen
        SDL_GL_SwapWindow(this->window_resource.ptr());
    }

private:
    SDL_GLContext context;
    concurrent::resource_property<SDL_Window> window_resource;

};// class sdl_window