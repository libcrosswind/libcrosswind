#version 130
//Fragment shader

in vec4 fragment_color; //input color

out vec4 color;		 //output color


void main() {
    vec4 textureColor = fragment_color;
    color = textureColor;
}