#version 420 core
layout (triangles, invocations = 2) in;
layout (triangle_strip, max_vertices = 3) out;

layout(std140, binding = 0) uniform transform_block
{
    mat4 mvp_matrix[2];
};

in VS_OUT
{
	vec3 text_coords;
} gs_in[];

out GS_OUT
{
	vec3 text_coords;
} gs_out;

void main(void)
{
    for (int i = 0; i < gl_in.length(); i++)
    {
		gs_out.text_coords = gs_in[i].text_coords;
        gl_Position =  gl_in[i].gl_Position; //mvp_matrix[gl_InvocationID] *
        gl_ViewportIndex = gl_InvocationID;
        EmitVertex();
    }
    EndPrimitive();
}


