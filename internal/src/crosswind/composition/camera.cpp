#include "crosswind/composition/camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

cw::composition::camera::camera(const glm::vec2& screen_size):
needs_matrix_update(true),
screen_dimension(screen_size),
scale(1.0f, 1.0f, 0.0f),
position(0.0f, 0.0f, 0.0f), 
camera_matrix(1.0f),
ortho_matrix(1.0f){

	ortho_matrix = glm::ortho(0.0f, screen_dimension.x, 0.0f, screen_dimension.y);
}

void cw::composition::camera::set_position(const glm::vec3& new_position){
	position = new_position;
    needs_matrix_update = true;
}

glm::vec3 cw::composition::camera::get_position(){
	return position;
}

void cw::composition::camera::set_scale(const float& new_scale){
	scale.x = new_scale;
	scale.y = new_scale;	
	scale.z = 0.0f;
    needs_matrix_update = true;
}

float cw::composition::camera::get_scale(){
	return scale.x;	// whichever works
}

glm::mat4 cw::composition::camera::get_camera_matrix(){

	return camera_matrix;	

}

void cw::composition::camera::update(const float& delta){
	if(needs_matrix_update){
        glm::vec3 translate(-position.x + screen_dimension.x / 2, -position.y + screen_dimension.y/ 2, 0.0f);
        camera_matrix = glm::translate(ortho_matrix, translate);
        camera_matrix = glm::scale(glm::mat4(1.0f), scale) * camera_matrix;
        needs_matrix_update = false;
	}
}

glm::vec2 cw::composition::camera::convert_screen_to_world(const glm::vec2& screen_coordinates) {
    auto world_coordinates = screen_coordinates;
	world_coordinates.y = screen_dimension.y - world_coordinates.y;
	world_coordinates -= glm::vec2(screen_dimension.x / 2, screen_dimension.y / 2);
	world_coordinates /= glm::vec2(scale.x, scale.y);
	world_coordinates += glm::vec2(position.x, position.y);
    return world_coordinates;
}
 