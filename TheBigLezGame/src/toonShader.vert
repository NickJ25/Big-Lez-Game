#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texCoords;
layout (location = 3) in ivec4 bone_ids;     // INT pointer
layout (location = 4) in vec4 weights;

uniform mat4 model; // Replaces M_matrix
uniform mat4 view; // Replace V
uniform mat4 projection; // Replace normals_matrix
uniform mat4 normals; // Replaces normals_matrix

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

// Additional Ones
out vec4 ModelView; // Replaces viewSpace
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

const int MAX_BONES = 100;
uniform mat4 bones[MAX_BONES];

void main( )
{
	mat4 bone_transform = bones[bone_ids[0]] * weights[0];
		bone_transform += bones[bone_ids[1]] * weights[1];
		bone_transform += bones[bone_ids[2]] * weights[2];
		bone_transform += bones[bone_ids[3]] * weights[3];

	vec4 boned_position = bone_transform * vec4(in_position, 1.0); 

	ModelView = view * model * boned_position;

	Normal = normalize(vec3(normals * (bone_transform * vec4(in_normal, 0.0f))));

	// In camera space, the camera is at the origin
	EyeDirection_cameraspace = vec3(0.0f, 0.0f, 0.0f) - (view * model * boned_position).xyz;

	// Vector that goes from the vertex to the light in camera space
	LightDirection_cameraspace = (view * vec4(0.0f, 0.0f, 0.0f, 0.0f)).xyz;

	

	FragPos = vec3(model * boned_position);
    TexCoords = in_texCoords;

	 gl_Position = (projection * view *  model) * boned_position;
}