#version 130
//Vertex shader

//VBO input data.
in vec3 vertex_position;
in vec4 vertex_color;

out vec4 fragment_color;

void main() {
    gl_Position.xyz = vertex_position;
    
    //Normalized coordinates
    gl_Position.w = 1.0;

    fragment_color = vertex_color;
}