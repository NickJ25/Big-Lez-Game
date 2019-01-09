#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 colour;


out vec3 o_Colour;
out vec2 o_texCoord;

uniform mat4 imgRotation;

void main()
{
	vec4 newPosition = vec4(position,1.0f) * imgRotation;
    gl_Position = vec4(newPosition.xyz, 1.0);
	o_Colour = colour;
	o_texCoord = texCoord;
}