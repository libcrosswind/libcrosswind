#pragma once

#include <glm/glm.hpp>

#include <crosswind/geometry/rectangle.hpp>
#include <crosswind/simulation/detail/standard_actor.hpp>
#include <crosswind/simulation/detail/graphical_actor.hpp>
#include <crosswind/simulation/gl/gl_vbo.hpp>

namespace cw{
namespace simulation{

	class sprite;

}// namespace simulation
}// namespace cw

class cw::simulation::sprite: 	public cw::geometry::rectangle,
	                            public cw::simulation::detail::standard_actor,
                              	public cw::simulation::detail::graphical_actor,
                              	public cw::simulation::gl::gl_vbo{

public:
	sprite(const glm::vec3& p, const glm::vec3& s): rectangle(p, s){
        upload_vertex_array(vertices);
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

	virtual void draw(){
		draw_vertex_array(vertices);
	}

};// class sprite