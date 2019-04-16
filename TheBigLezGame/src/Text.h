#pragma once
#include "Shader.h"
#include <iostream>
#include "ft2build.h"
#include "glm/glm.hpp"
#include <string>
#include <map>
#include "Input.h"

#include FT_FREETYPE_H

struct Character
{
	GLuint textureID; // glyph texture
	glm::ivec2 size; // size of glyth
	glm::vec2 bearing; // of
	GLuint advance;
};

class Text
{
private:
	void initText(const char* font);

	std::map<GLchar, Character> characters;
	Shader* m_textShader;
	GLuint m_VAO, m_VBO;
	glm::vec2 m_textBoxSize;
	bool m_centreText;				// Should text draw in centre

	glm::mat4 m_model = glm::mat4(1.0);
	glm::mat4 m_proj = glm::mat4(1.0);
	glm::mat4 m_view = glm::mat4(1.0);
	
public:
	Text(glm::vec2 position, const char* font);
	~Text();

	void move(glm::vec2 position);
	glm::vec2 getPosition();
	void scale(glm::vec2 scale);

	glm::vec2 getSize();
	void draw(std::string text, glm::vec4 colour, int imageMode);
	void draw(std::string text, glm::vec4 colour, int imageMode, int viewport);
};