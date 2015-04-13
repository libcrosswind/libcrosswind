#pragma once

#include "glm/glm.hpp"

namespace cw{
namespace composition{

class camera{
public: 
	camera(const glm::vec2& screen_size);

	void set_position(const glm::vec3& new_position);

	glm::vec3 get_position();

	void set_scale(const float& new_scale);

	float get_scale();

	glm::mat4 get_camera_matrix();

	void update(const float& delta);

    glm::vec2 convert_screen_to_world(const glm::vec2& screen_coordinates);

private:
    bool needs_matrix_update;
    glm::vec2 screen_dimension;
	glm::vec3 scale;
	glm::vec3 position;
	glm::mat4 camera_matrix;
	glm::mat4 ortho_matrix;

};// class camera

}// namespace composition
}// namespace cw