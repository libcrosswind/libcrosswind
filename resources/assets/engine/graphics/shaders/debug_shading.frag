#version 310 es
//Fragment shader

in vec4 fragment_color; //input color

out vec4 color;		 //output color


void main() {
    vec4 textureColor = fragment_color;
    color = textureColor;
}