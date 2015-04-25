#version 130
//Fragment shader

in vec4 fragment_color;

//Output to screen
out vec4 color;

void main() {
    color = fragment_color;
}