#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <crosswind/simulation/detail/interactive_actor.hpp>
#include <crosswind/simulation/detail/standard_actor.hpp>

namespace cw{
namespace simulation{

		class camera;

}// namespace simulation
}// namespace cw

class cw::simulation::camera: public detail::interactive_actor,
							  public detail::standard_actor{
public: 
	camera(int screen_width, int screen_height):
    needs_matrix_update(true),
    screen_dimension(glm::vec2(screen_width, screen_height)),
	scale(1.0f, 1.0f, 0.0f),
	position(0.0f, 0.0f, 0.0f), 
	camera_matrix(1.0f),
    ortho_matrix(1.0f){
		ortho_matrix = glm::ortho(0.0f, screen_dimension.x, 0.0f, screen_dimension.y);
	}

	void handle_event(SDL_Event* e){
		switch(e->type){
			case SDL_KEYDOWN:{
				switch(e->key.keysym.sym){
					case SDLK_w:
						set_position(get_position() + glm::vec3(0.0f, 10.0f, 0.0f));
					break;

					case SDLK_s:
						set_position(get_position() + glm::vec3(0.0f, -10.0f, 0.0f));
					break;

                    case SDLK_a:
                        set_position(get_position() + glm::vec3(-10.0f, 0.0f, 0.0f));
                        break;

                    case SDLK_d:
                        set_position(get_position() + glm::vec3(10.0f, 0.0f, 0.0f));
                    break;

                    case SDLK_q:
                        set_scale(get_scale() + 0.1);
                        break;
                    case SDLK_e:
                        set_scale(get_scale() - 0.1);
                    break;

				}
			}
			break;
		}
	}

	void trigger(std::shared_ptr<detail::event_mapping> mappint){

	}

	void set_position(const glm::vec3& new_position){	
		position = new_position;
        needs_matrix_update = true;
    }
	
	glm::vec3 get_position(){
		return position;
	}

	void set_scale(float new_scale){ 	
		scale.x = new_scale;
		scale.y = new_scale;	
		scale.z = 0.0f;
        needs_matrix_update = true;
    }

	float get_scale(){
		return scale.x;	// whichever works
	}

	auto get_camera_matrix(){	
	
		return camera_matrix;	
	
	}

	void update(double delta){
		if(needs_matrix_update){
            glm::vec3 translate(-position.x + screen_dimension.x / 2, -position.y + screen_dimension.y/ 2, 0.0f);
            camera_matrix = glm::translate(ortho_matrix, translate);
            camera_matrix = glm::scale(glm::mat4(1.0f), scale) * camera_matrix;
            needs_matrix_update = false;
		}
	}

private:
    bool needs_matrix_update;
    glm::vec2 screen_dimension;
	glm::vec3 scale;
	glm::vec3 position;
	glm::mat4 camera_matrix;
	glm::mat4 ortho_matrix;

};// class camera