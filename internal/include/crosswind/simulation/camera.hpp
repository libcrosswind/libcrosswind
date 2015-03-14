#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <crosswind/simulation/detail/interactive_actor.hpp>
#include <crosswind/simulation/detail/standard_actor.hpp>

#include <crosswind/platform/backend/interface/core/input_listener.hpp>

namespace cw{
namespace simulation{

		class camera;

}// namespace simulation
}// namespace cw

#include <iostream>

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

    void handle_input(std::shared_ptr<platform::backend::interface::core::input_listener> input_listener){
        if(input_listener->is_key_down("w")){
            set_position(get_position() + glm::vec3(0.0f, 10.0f, 0.0f));
        }

        if(input_listener->is_key_down("s")){
            set_position(get_position() + glm::vec3(0.0f, -10.0f, 0.0f));
        }

        if(input_listener->is_key_down("a")){
            set_position(get_position() + glm::vec3(-10.0f, 0.0f, 0.0f));
        }

        if(input_listener->is_key_down("d")){
            set_position(get_position() + glm::vec3(10.0f, 0.0f, 0.0f));
        }

        if(input_listener->is_key_down("q")){
            set_scale(get_scale() + 0.1);
        }

        if(input_listener->is_key_down("e")){
            set_scale(get_scale() - 0.1);
        }

        if(input_listener->is_key_down("mouse_left")){
            std::cout
                        << "X: " << convert_screen_to_world(input_listener->get_mouse_coordinates()).x
                        << " Y: " << convert_screen_to_world(input_listener->get_mouse_coordinates()).y
                        <<
            std::endl;
        }
    }

	void trigger(std::shared_ptr<detail::event_mapping> mapping){

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

    glm::mat4 get_camera_matrix(){
	
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

    glm::vec2 convert_screen_to_world(glm::vec2 screen_coordinates) {
        screen_coordinates.y = screen_dimension.y - screen_coordinates.y;
        screen_coordinates -= glm::vec2(screen_dimension.x / 2, screen_dimension.y / 2);
        screen_coordinates /= glm::vec2(scale.x, scale.y);
        screen_coordinates += glm::vec2(position.x, position.y);
        return screen_coordinates;
    }

private:
    bool needs_matrix_update;
    glm::vec2 screen_dimension;
	glm::vec3 scale;
	glm::vec3 position;
	glm::mat4 camera_matrix;
	glm::mat4 ortho_matrix;

};// class camera