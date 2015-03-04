#pragma once

#include <SDL2/SDL_opengl.h>

#include <crosswind/math/vector3.hpp>
#include <crosswind/platform/sdl/sdl_gl_renderer.hpp>
#include <crosswind/simulation/detail/object.hpp>
#include <crosswind/simulation/detail/standard_actor.hpp>
#include <crosswind/simulation/detail/graphical_actor.hpp>

namespace cw{
namespace geometry{

	class cube;

}// namespace geometry
}// namespace cw


class cw::geometry::cube:   public cw::simulation::detail::object,
                            public cw::simulation::detail::standard_actor,
                            public cw::simulation::detail::graphical_actor{
public:
	cube(const math::vector3& p,
         const math::vector3& s): object(p, s){

        // front face
        vertices.push_back({  s[0]/2,  s[1]/2,  s[2]/2 });
        vertices.push_back({ -s[0]/2,  s[1]/2,  s[2]/2 });
        vertices.push_back({ -s[0]/2, -s[1]/2,  s[2]/2 });
        vertices.push_back({  s[0]/2, -s[1]/2,  s[2]/2 });

        // left face
        vertices.push_back({-s[0]/2,  s[1]/2,  s[2]/2});
        vertices.push_back({-s[0]/2,  s[1]/2, -s[2]/2});
        vertices.push_back({-s[0]/2, -s[1]/2, -s[2]/2});
        vertices.push_back({-s[0]/2, -s[1]/2,  s[2]/2});

        // back face
        vertices.push_back({ s[0]/2,  s[1]/2, -s[2]/2});
        vertices.push_back({-s[0]/2,  s[1]/2, -s[2]/2});
        vertices.push_back({-s[0]/2, -s[1]/2, -s[2]/2});
        vertices.push_back({ s[0]/2, -s[1]/2, -s[2]/2});

        // right face
        vertices.push_back({s[0]/2,  s[1]/2, -s[2]/2});
        vertices.push_back({s[0]/2,  s[1]/2,  s[2]/2});
        vertices.push_back({s[0]/2, -s[1]/2,  s[2]/2});
        vertices.push_back({s[0]/2, -s[1]/2, -s[2]/2});

        // top face
        vertices.push_back({-s[0]/2, s[1]/2,  s[2]/2});
        vertices.push_back({-s[0]/2, s[1]/2,  s[2]/2});
        vertices.push_back({ s[0]/2, s[1]/2, -s[2]/2});
        vertices.push_back({ s[0]/2, s[1]/2, -s[2]/2});

        // bottom face
        vertices.push_back({ s[0]/2, -s[1]/2,  s[2]/2});
        vertices.push_back({-s[0]/2, -s[1]/2,  s[2]/2});
        vertices.push_back({-s[0]/2, -s[1]/2, -s[2]/2});
        vertices.push_back({ s[0]/2, -s[1]/2, -s[2]/2});
	}

	virtual void update(double delta){

/*        delta_count += delta;

        auto& a = animations.data.acquire();

        if(delta_count >= a["current"]->duration / a["current"]->frames.size()){

            delta_count = 0;

            a["current"]->current_frame++;

            if(a["current"]->current_frame >= a["current"]->frames.size()){
                a["current"]->current_frame = 0;
            }
        }

        swap_graphical_item(sprites, "current", a["current"]->frames[a["current"]->current_frame]);

        animations.data.release();*/
    }

	virtual void render(std::shared_ptr<platform::sdl::sdl_gl_renderer> sdl_gl_renderer){

		sdl_gl_renderer->draw_quads(vertices);

	}

};