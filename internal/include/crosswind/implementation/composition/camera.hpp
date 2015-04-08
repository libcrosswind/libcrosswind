#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <crosswind/interface/composition/camera.hpp>

namespace cw{
namespace implementation{
namespace composition{

		class camera;

}// namespace composition
}// namespace implementation
}// namespace cw

class cw::implementation::composition::camera: public cw::interface::composition::camera{
public: 
	camera(const glm::vec2& screen_size):
	interface::composition::camera(screen_size){
		ortho_matrix = glm::ortho(0.0f, screen_dimension.x, 0.0f, screen_dimension.y);
	}

	virtual ~camera(){

	}

	virtual void set_position(const glm::vec3& new_position){
		position = new_position;
        needs_matrix_update = true;
    }

	virtual glm::vec3 get_position(){
		return position;
	}

	virtual void set_scale(const float& new_scale){
		scale.x = new_scale;
		scale.y = new_scale;	
		scale.z = 0.0f;
        needs_matrix_update = true;
    }

	virtual float get_scale(){
		return scale.x;	// whichever works
	}

	virtual glm::mat4 get_camera_matrix(){
	
		return camera_matrix;	
	
	}

	virtual void update(const float& delta){
		if(needs_matrix_update){
            glm::vec3 translate(-position.x + screen_dimension.x / 2, -position.y + screen_dimension.y/ 2, 0.0f);
            camera_matrix = glm::translate(ortho_matrix, translate);
            camera_matrix = glm::scale(glm::mat4(1.0f), scale) * camera_matrix;
            needs_matrix_update = false;
		}
	}

    virtual glm::vec2 convert_screen_to_world(const glm::vec2& screen_coordinates) {
        auto world_coordinates = screen_coordinates;
		world_coordinates.y = screen_dimension.y - world_coordinates.y;
		world_coordinates -= glm::vec2(screen_dimension.x / 2, screen_dimension.y / 2);
		world_coordinates /= glm::vec2(scale.x, scale.y);
		world_coordinates += glm::vec2(position.x, position.y);
        return world_coordinates;
    }

};// class camera                                                                                                                                                                           