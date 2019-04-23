#version 420 core
layout (triangles, invocations = 2) in;
layout (triangle_strip, max_vertices = 3) out;

uniform int viewportNum;
uniform mat4 imgProj;

in VS_OUT
{
	vec2 o_texCoord;
} gs_in[];

out GS_OUT
{
	vec2 o_texCoord;
} gs_out;

void main(void)
{
    for (int i = 0; i < gl_in.length(); i++)
    {
		gs_out.o_texCoord = gs_in[i].o_texCoord;
        gl_Position = imgProj * gl_in[i].gl_Position;
        gl_ViewportIndex = viewportNum;
        EmitVertex();
    }
    EndPrimitive();
}