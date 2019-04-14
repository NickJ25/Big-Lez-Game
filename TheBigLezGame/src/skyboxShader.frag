#version 330 core

//in vec3 text_coords;

in GS_OUT
{
 	vec3 text_coords;
} fs_in;

out vec4 f_color;

uniform samplerCube skybox;

void main()
{

	f_color = texture( skybox, fs_in.text_coords);
	
}