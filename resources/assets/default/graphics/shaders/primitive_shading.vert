#version 130
//Vertex shader

//VBO input data.
in vec4 vertex_position; 
in vec4 vertex_color; 

out vec4 fragment_color;

uniform mat4 projection_matrix;

void main() {
    gl_Position = projection_matrix * vertex_position;
    fragment_color = vertex_color;
}