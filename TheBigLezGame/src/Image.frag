#version 430
out vec4 FragColor;

in vec3 o_Colour;
in vec2 o_texCoord;

uniform sampler2D texImage;

void main()
{
   FragColor = texture(texImage, o_texCoord);
} 