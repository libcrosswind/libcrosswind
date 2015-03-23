#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cw{
namespace interface{
namespace composition{

	class camera;

}// namespace composition
}// namespace interface
}// namespace cw

class cw::interface::composition::camera{
public: 
	camera(const glm::vec2& screen_size):
    needs_matrix_update(true),
    screen_dimension(screen_size),
	scale(1.0f, 1.0f, 0.0f),
	position(0.0f, 0.0f, 0.0f), 
	camera_matrix(1.0f),
    ortho_matrix(1.0f){
		ortho_matrix = glm::ortho(0.0f, screen_dimension.x, 0.0f, screen_dimension.y);
	}

	virtual void set_position(const glm::vec3& new_position) = 0;
	
	virtual glm::vec3 get_position() = 0;

	virtual void set_scale(float new_scale) = 0;

	virtual float get_scale() = 0;

    virtual glm::mat4 get_camera_matrix() = 0;

	virtual void update(float delta) = 0;

    virtual glm::vec2 convert_screen_to_world(glm::vec2 screen_coordinates) = 0;

private:
    bool needs_matrix_update;
    glm::vec2 screen_dimension;
	glm::vec3 scale;
	glm::vec3 position;
	glm::mat4 camera_matrix;
	glm::mat4 ortho_matrix;

};// class camera