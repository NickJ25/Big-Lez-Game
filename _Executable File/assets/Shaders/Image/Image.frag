#version 430
out vec4 FragColor;

//in vec2 o_texCoord;

in GS_OUT
{
 	vec2 o_texCoord;
} fs_in;


uniform sampler2D texImage;
uniform vec3 imgColour;
uniform int imgMode;
uniform float alpha;
vec4 finalColour;

void main()
{
	if(imgMode == 1){
		finalColour = vec4(1.0, 1.0, 1.0, texture(texImage, fs_in.o_texCoord).r);
		if(finalColour.w <= 0.2) discard;
		finalColour = vec4(imgColour, alpha) * vec4(vec3(finalColour), alpha);
		if(alpha <= 0.01) discard;
	} else {
		finalColour = texture(texImage, fs_in.o_texCoord);
	}

	FragColor = finalColour;
} 