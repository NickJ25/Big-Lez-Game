#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out VS_OUT
{
	vec2 o_texCoord;
} vs_out;

//out vec2 o_texCoord;

uniform mat4 imgRotation;
uniform mat4 imgProj;
uniform mat4 imgView;
//mat4 modelMat = new mat4(1.0f);

void main()
{
	vec4 newPosition = (imgView * imgRotation) * vec4(position, 1.0f); //imgProj * 
    gl_Position = vec4(newPosition.xyz, 1.0f);
	vs_out.o_texCoord = texCoord;
}