// Phong fragment shader phong-tex.frag matched with phong-tex.vert
#version 330

// Some drivers require the following
precision highp float;

struct lightStruct
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct materialStruct
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform lightStruct light;
uniform materialStruct material;

in vec3 ex_N;
in vec3 ex_V;
in vec3 ex_L;
in float ex_Att;
layout(location = 0) out vec4 out_Color;


void main(void) {
    
	// Ambient intensity
	vec4 ambientI = light.ambient * material.ambient;

	// Diffuse intensity
	vec4 diffuseI = light.diffuse * material.diffuse;
	diffuseI = diffuseI * max(dot(normalize(ex_N),normalize(ex_L)),0);

	// Specular intensity
	// Calculate R - reflection of light
	vec3 R = normalize(reflect(normalize(-ex_L),normalize(ex_N)));

	vec4 specularI = light.specular * material.specular;
	specularI = specularI * pow(max(dot(R,ex_V),0), material.shininess);

	vec4 lighting = ex_Att*(diffuseI + specularI);

	vec4 litColour = ambientI + vec4(lighting.rgb, 1.0);
	vec4 shade1 = smoothstep(vec4(0.2), vec4(0.21), litColour);
	vec4 shade2 = smoothstep(vec4(0.4), vec4(0.41), litColour);
	vec4 shade3 = smoothstep(vec4(0.8), vec4(0.81), litColour);

	vec4 colour = max(max(0.3*shade1,0.5*shade2), shade3);

	// Fragment colour
	out_Color = colour;
}
