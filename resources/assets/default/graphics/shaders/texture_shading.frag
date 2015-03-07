#version 130
//Fragment shader

in vec2 fragment_uv; //uv coordinates

out vec4 color;		 //output color

uniform sampler2D texture_sampler;

void main() {
    vec4 textureColor = texture(texture_sampler, fragment_uv);
    color = textureColor;
}