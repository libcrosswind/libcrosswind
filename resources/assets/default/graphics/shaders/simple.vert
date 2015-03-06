#version 130

in vec3 vertex_position;

out vec3 fragment_color;




void main(){
	gl_Position.xyz = vertex_position;
	gl_Position.w = 1.0;

	fragment_color = vec3(vertex_position.x/3, vertex_position.y/4, vertex_position.x/2);
	if(fragment_color.x < 0){
		fragment_color.x = fragment_color.x * -1;
	}

	if(fragment_color.y < 0){
		fragment_color.y = fragment_color.y * -1;
	}

	if(fragment_color.z < 0){
		fragment_color.z = fragment_color.z * -1;
	}
}