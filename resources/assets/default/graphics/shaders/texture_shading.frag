#version 130
//Fragment shader

in vec2 fragment_uv; //uv coordinates
in float fragment_alpha;

out vec4 color;		 //output color

uniform sampler2D texture_sampler;

void main() {
    vec4 texture_color = texture(texture_sampler, fragment_uv);

    if(texture_color.a == 1.0f){
    	texture_color.a = fragment_alpha;
    }
    
    color = texture_color;
}