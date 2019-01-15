#include "Text.h"

Text::Text(glm::vec2 position)
{
	m_proj = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 100.0f);
	m_view = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

Text::~Text()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteProgram(m_textShader->getID());
}

void Text::draw(std::string text, glm::vec3 colour)
{
	m_textShader->use();

	glUniformMatrix4fv(glGetUniformLocation(m_textShader->getID(), "imgRotation"), 1, GL_FALSE, glm::value_ptr(m_model));
	glUniformMatrix4fv(glGetUniformLocation(m_textShader->getID(), "imgProj"), 1, GL_FALSE, glm::value_ptr(m_proj));
	glUniformMatrix4fv(glGetUniformLocation(m_textShader->getID(), "imgView"), 1, GL_FALSE, glm::value_ptr(m_view));

	//glUniformMatrix4fv(glGetUniformLocation(m_textShader->getID(), "PROJECTION_matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
	glUniform3f(glGetUniformLocation(m_textShader->getID(), "text_color"), colour.x, colour.y, colour.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_VAO);

	float offset_x = 0.0f; // offset to next char
	float offset_y = 0.0f; // offset to next char

	// iterate through each character within the string
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		float x_pos = offset_x + ch.bearing.x;
		float y_pos = offset_y - (ch.size.y - ch.bearing.y);

		float w = ch.size.x;
		float h = ch.size.y;

		// update VBO for each character
		float vertices[6][5] =
		{	// x			// y		// z	// texture
			{ x_pos,		y_pos + h,  0.0f,	0.0, 0.0 },
		{ x_pos,		y_pos,		0.0f,	0.0, 1.0 },
		{ x_pos + w,	y_pos,		0.0f,	1.0, 1.0 },

		{ x_pos,		y_pos + h,  0.0f,	0.0, 0.0 },
		{ x_pos + w,	y_pos,		0.0f,	1.0, 1.0 },
		{ x_pos + w,	y_pos + h,  0.0f,	1.0, 0.0 },
		};
		// render texture over this quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// update VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		offset_x += (ch.advance >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
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
