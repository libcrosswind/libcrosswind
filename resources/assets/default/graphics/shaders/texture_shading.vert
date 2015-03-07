#version 130
//Vertex shader

//VBO input data.
in vec3 vertex_position; 

out vec2 fragment_uv;

void main() {
    gl_Position.xyz = vertex_position;
    
    //Normalized coordinates
    gl_Position.w = 1.0;
    
    fragment_uv = vec2(vertexUV.x, 1.0 - vertexUV.y);
}