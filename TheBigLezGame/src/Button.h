#pragma once
#include <GL/glew.h>
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "MenuState.h"
#include "Image.h"
#include "Text.h"

class Button {
private:
	struct AABB
	{
		glm::vec2 centre;
		float width, height;
	};
	GLfloat m_width = 300;
	GLfloat m_height = 120;

	Image* m_texNormal, *m_texHover, *m_texClick;
	Image* m_currentImage; 

	Text* m_textBox;
	std::string m_text;

	glm::vec2 m_position;
	AABB* m_buttonCollision;

	// Add audio for hoovering over the button
public:
	Button(glm::vec2 position, std::string button_text); // ,MenuState* destination
	~Button();
	void update(glm::vec2* mousePos);
	void draw();
};