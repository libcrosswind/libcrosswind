#version 330 core
//Fragment shader

in mediump vec2 fragment_uv; //uv coordinates
in mediump float fragment_alpha;

out mediump vec4 color;		 //output color

uniform lowp sampler2D texture_sampler;

void main() {

    mediump vec4 texture_color = texture(texture_sampler, fragment_uv);
    texture_color.a = texture_color.a * fragment_alpha;
    color = texture_color;
    
}
