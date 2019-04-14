#version 330 core

layout(location = 0) in vec3 in_position;

//out vec3 text_coords;

//uniform mat4 VP; //   WITHOUT model matrix

out VS_OUT
{
	vec3 text_coords;
} vs_out;

void main()
{
	vec4 pos = vec4( in_position, 1.0); //VP * 
	gl_Position = pos.xyww; // optimization !! its work with glDepthFunc(GL_LEQUAL);
							// and draw skybox after scene !!!

	vs_out.text_coords = in_position;
}