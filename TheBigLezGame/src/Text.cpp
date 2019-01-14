#include "Text.h"

Text::Text(glm::vec2 position)
{

}

Text::~Text()
{

}

void Text::draw(std::string text, glm::vec3 colour)
{

}

void Text::initText()
{
	FT_Library ft_lib;
	if (FT_Init_FreeType(&ft_lib)) std::cout << "free type init error" << std::endl;

	FT_Face ft_face;
	if (FT_New_Face(ft_lib, "fonts/ariali.ttf", 0, &ft_face)) std::cout << "font NOT load" << std::endl;

	FT_Set_Pixel_Sizes(ft_face, 0, 48); //width to 0 lets the face dynamically calculate the width based on the given height.

											// Disable byte-alignment restriction  ????????????????????
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // use a single byte to represent the colors of a texture (like freetype)

	for (int c = 32; c < 127; c++) //unsigned char 0 - 255 (1 byte = 8 bit)
	{
		// load character glyph
		if (FT_Load_Char(ft_face, c, FT_LOAD_RENDER))
		{
			std::cout << "error load character: " << (char)c << std::endl;
			continue;
		}
		// generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, ft_face->glyph->bitmap.buffer);

		// texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		// store character in map
		Character character = { texture, glm::ivec2(ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows), 
			glm::ivec2(ft_face->glyph->bitmap_left, ft_face->glyph->bitmap_top), ft_face->glyph->advance.x };

		characters.insert(std::pair<GLchar, Character>(c, character));
	}
}
