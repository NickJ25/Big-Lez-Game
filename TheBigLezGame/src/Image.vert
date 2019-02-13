#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 o_texCoord;

uniform mat4 imgRotation;
uniform mat4 imgProj;
uniform mat4 imgView;
//mat4 modelMat = new mat4(1.0f);

void main()
{
	vec4 newPosition = (imgProj * imgView * imgRotation) * vec4(position, 1.0f);
    gl_Position = vec4(newPosition.xyz, 1.0f);
	o_texCoord = texCoord;
}