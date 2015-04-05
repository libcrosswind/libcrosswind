#version 130
//Vertex shader

//VBO input data.
in vec4 vertex_position; 
in vec4 vertex_color; 
in vec2 vertex_uv;

out float fragment_alpha;
out vec2 fragment_uv;

uniform mat4 projection_matrix;

void main() {
    gl_Position = projection_matrix * vertex_position;
    fragment_uv = vec2(vertex_uv.x, 1.0 - vertex_uv.y);
    fragment_alpha = vertex_color.a;
}