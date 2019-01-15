#version 430
out vec4 FragColor;

in vec2 o_texCoord;

uniform sampler2D texImage;
uniform vec3 imgColour;
uniform int imgMode;

vec4 finalColour;

void main()
{
	if(imgMode == 1){
		finalColour = vec4(1.0, 1.0, 1.0, texture(texImage, o_texCoord).r);
		if(finalColour.w <= 0.2) discard;
		finalColour = vec4(imgColour, 1.0f) * finalColour;
	} else {
		finalColour = texture(texImage, o_texCoord);
	}

	FragColor = finalColour;
} 