#version 330 core
//Fragment shader

in mediump vec4 fragment_color;

//Output to screen
out mediump vec4 color;

void main() {
    color = fragment_color;
}