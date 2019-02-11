#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in ivec4 bone_ids;     // INT pointer
layout (location = 4) in vec4 weights;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Additional ones


out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

// Additional Ones
out vec4 viewSpace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

void main( )
{
	mat4 bone_transform = bones[bone_ids[0]] * weights[0];
		bone_transform += bones[bone_ids[1]] * weights[1];
		bone_transform += bones[bone_ids[2]] * weights[2];
		bone_transform += bones[bone_ids[3]] * weights[3];

	vec4 boned_position = bone_transform * vec4(in_position, 1.0); 



    gl_Position = projection * view *  model * vec4(position, 1.0f);
    FragPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoords = texCoords;
}