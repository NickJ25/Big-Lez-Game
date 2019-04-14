#version 420 core
layout (triangles, invocations = 2) in;
layout (triangle_strip, max_vertices = 3) out;

layout(std140, binding = 0) uniform transform_block
{
    mat4 mvp_matrix[2];
};

in VS_OUT
{
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
    vec4 ModelView;
    vec3 EyeDirection_cameraspace;
    vec3 LightDirection_cameraspace;
} gs_in[];

out GS_OUT
{
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
    vec4 ModelView;
    vec3 EyeDirection_cameraspace;
    vec3 LightDirection_cameraspace;
} gs_out;

void main(void)
{
    for (int i = 0; i < gl_in.length(); i++)
    {
        // Sending stuff to the frag
        gs_out.Normal = gs_in[i].Normal;
        gs_out.FragPos = gs_in[i].FragPos;
        gs_out.TexCoords = gs_in[i].TexCoords;
        gs_out.ModelView = gs_in[i].ModelView;
        gs_out.EyeDirection_cameraspace = gs_in[i].EyeDirection_cameraspace;
        gs_out.LightDirection_cameraspace = gs_in[i].LightDirection_cameraspace;

        gl_Position = mvp_matrix[gl_InvocationID] * gl_in[i].gl_Position;
        gl_ViewportIndex = gl_InvocationID;
        EmitVertex();
    }
    EndPrimitive();
}


