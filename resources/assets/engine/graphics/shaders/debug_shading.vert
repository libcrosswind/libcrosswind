#version 310 es
//Vertex shader

//VBO input data.
in vec4 vertex_position; 
in vec4 vertex_color; 
in vec2 vertex_uv; 

out vec4 fragment_color;


void main() {
    gl_Position = vertex_position;
    fragment_color = vertex_color;
}