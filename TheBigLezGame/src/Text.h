#pragma once
#include "Shader.h"
#include <iostream>
#include "ft2build.h"
#include "glm/glm.hpp"
#include <string>
#include <map>

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
public:
	Text(glm::vec2 position);
	~Text();
	void draw(std::string text, glm::vec3 colour);
private:
	void initText();
	std::map<GLchar, Character> characters;
};