#version 420 core
layout (triangles, invocations = 2) in;
layout (triangle_strip, max_vertices = 3) out;


uniform int viewportNum;

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
        gl_Position =  gl_in[i].gl_Position;
        gl_ViewportIndex = viewportNum;
        EmitVertex();
    }
    EndPrimitive();
}


