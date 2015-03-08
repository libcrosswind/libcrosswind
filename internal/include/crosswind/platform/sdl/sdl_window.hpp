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
namespace sdl{

	class sdl_window;

}// namespace sdl
}// namespace platform
}// namespace cw

class cw::platform::sdl::sdl_window{
public:

	sdl_window(const std::string& window_title, const glm::vec4& bounds, const unsigned int& flags):
            window(SDL_CreateWindow,
                   SDL_DestroyWindow,
                   window_title.c_str(),
                   bounds[0], bounds[1], bounds[2], bounds[3],
                   flags){

		title.set = [this](const std::string& text){
			SDL_SetWindowTitle(this->window.ptr(), title.get().c_str());
		};

		title.get = [this](){
			std::string text;
			text = SDL_GetWindowTitle(this->window.ptr());
			return text;
		};

		brightness.set = [this](const float& bright){
			if (SDL_SetWindowBrightness(this->window.ptr(), brightness) != 0)
				throw sdl_exception("SDL_SetWindowBrightness");
        };

		brightness.get = [this](){
			float bright;
            bright = SDL_GetWindowBrightness(this->window.ptr());
			return bright;
		};

        position.set = [this](const glm::vec2& new_position){
            SDL_SetWindowPosition(this->window.ptr(), new_position.x, new_position.y);
        };

        position.get = [this](){
            int x, y;
            SDL_GetWindowPosition(this->window.ptr(), &x, &y);
            return glm::vec2(x, y);
        };


		size.set = [this](const glm::vec2& new_size){
			SDL_SetWindowSize(this->window.ptr(), new_size.x, new_size.y);
		};

		size.get = [this](){
			int w, h;
			SDL_GetWindowSize(this->window.ptr(), &w, &h);
			return glm::vec2(w, h);
		};

        context = SDL_GL_CreateContext(this->window.ptr());
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

        set_clear_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    ~sdl_window(){
        SDL_GL_DeleteContext(context);
    }

	void maximize() {
		SDL_MaximizeWindow(this->window.ptr());
	}

	void minimize() {
		SDL_MinimizeWindow(this->window.ptr());
	}

	void show() {
		SDL_ShowWindow(this->window.ptr());
	}

	void hide() {
		SDL_HideWindow(this->window.ptr());
	}

	void restore() {
		SDL_RestoreWindow(this->window.ptr());
	}

	void raise() {
		SDL_RaiseWindow(this->window.ptr());
	}

    void set_clear_color(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void clear() {
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void present() {
        //Update screen
        SDL_GL_SwapWindow(this->window.ptr());
    }

public:
    concurrent::hollow_property<std::string> title;
    concurrent::hollow_property<float> brightness;
    concurrent::hollow_property<glm::vec2> position;
    concurrent::hollow_property<glm::vec2> size;

private:
    SDL_GLContext context;
    concurrent::resource_property<SDL_Window> window;

};// class sdl_window