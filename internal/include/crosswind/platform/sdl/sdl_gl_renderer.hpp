#pragma once

#include <memory>
#include <string>
#include <vector>

#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>

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

        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, gl_version[0] );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, gl_version[1] );

        /*        context = std::make_unique<concurrent::resource_property<void> >
                (SDL_GL_CreateContext, SDL_GL_DeleteContext, args...);
        */

        context = SDL_GL_CreateContext(args...);

        auto error = GL_NO_ERROR;
        std::string error_string = "";

        //Vsync
        if(SDL_GL_SetSwapInterval(1) < 0){
            error_string.append(SDL_GetError());

        	throw sdl_exception("Warning: Unable to set VSync! SDL Error: " + error_string);
		}


        //Initialize Projection Matrix
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();

        error = glGetError();
        //Check for error
        if(error != GL_NO_ERROR){
            error_string.append(reinterpret_cast<const char*>(gluErrorString(error)));
            throw sdl_exception("Error initializing OpenGL! " + error_string);
        }

        //Initialize Modelview Matrix
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        error = glGetError();

        //Check for error
        if(error != GL_NO_ERROR){
            error_string.append(reinterpret_cast<const char*>(gluErrorString(error)));
        	throw sdl_exception("Error initializing OpenGL! " + error_string);
        }

        glEnable(GL_DEPTH_TEST);

        error = glGetError();

        //Check for error
        if(error != GL_NO_ERROR){
            error_string.append(reinterpret_cast<const char*>(gluErrorString(error)));

        	throw sdl_exception("Error initializing OpenGL! " + error_string);
        }



	}

    ~sdl_gl_renderer(){
        SDL_GL_DeleteContext(context);  
	}

    void set_perspective(auto fovY, auto aspect, auto zNear, auto zFar){
        const auto pi = 3.1415926535897932384626433832795;
        auto fW = 0.0;
        auto fH = 0.0;
        fH = tan( fovY / 360 * pi ) * zNear;
        fW = fH * aspect;
        glFrustum( -fW, fW, -fH, fH, zNear, zFar );
    }

    void draw_triangles(concurrent::mutex_vector<cw::math::vector3>& vertices){
        glBegin(GL_TRIANGLES);
        draw_vertices(vertices);
        glEnd();

        //        glTranslatef(0.0f, 0.0f, 0.0f);
        //        glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
        //        glScalef(1.0f, 0.5f, 1.0f);
        /*        glBegin(GL_TRIANGLES);                      // Drawing Using Triangles
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f( 0.0f, 1.0f, 0.0f);              // Top
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f,-1.0f, 0.0f);              // Bottom Left
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f( 1.0f,-1.0f, 0.0f);              // Bottom Right
            glEnd();                            // Finished Drawing The Triangle
        */
    }

    void draw_quads(concurrent::mutex_vector<cw::math::vector3>& vertices){
        glBegin(GL_QUADS);
        draw_vertices(vertices);
        glEnd();
    }

    void load_identity(){
        glLoadIdentity();
    }

    void present(auto window_ptr) {

        //Update screen
    	SDL_GL_SwapWindow( window_ptr );
	}

    void clear() {
        //Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

    void set_draw_color(float r, float g, float b, float a = 1.f) {

        cw::math::clamp<float> clamp(0.f, 1.f);

        //Initialize clear color
        glClearColor(clamp(r), clamp(g), clamp(b), clamp(a));
	}

	SDL_GLContext context;
private:
    void draw_vertices(concurrent::mutex_vector<cw::math::vector3>& vertices){
        auto& container = vertices.data.acquire();
        for(auto vertex : container){
            glVertex3f(vertex[0], vertex[1], vertex[2]);
        }
        vertices.data.release();
    }

	//std::unique_ptr<concurrent::resource_property<void> > context;
};// class sdl_gl_renderer