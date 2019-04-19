#pragma once

//glew
#include <GL/glew.h>

//GLFW
#include <GLFW\glfw3.h>

//std library
#include <string>

//glm
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

//other files
#include "MenuState.h"
#include "Image.h"
#include "Text.h"
#include "Input.h"

class Button {
private:
	//collider
	struct AABB
	{
		glm::vec2 centre;
		float width, height;
	};

	//size variables
	GLfloat m_width = 300;
	GLfloat m_height = 120;

	//image files
	Image* m_texNormal, *m_texHover, *m_texClick;
	Image* m_currentImage; 

	//text variables
	Text* m_textBox;
	std::string m_text;
	bool m_buttonClick;

	//position variable and collision object
	glm::vec2 m_position;
	AABB* m_buttonCollision;

	// Add audio for hoovering over the button

	//check if a game or menu button
	bool isMenuButton;

public:
	const enum BUTTON_TYPE { NORMAL, ARROW };
	Button(BUTTON_TYPE type, glm::vec2 position, std::string button_text, bool isMenu = false); // ,MenuState* destination
	~Button();
	bool buttonClick();
	void draw();
	void rotate(GLfloat radians);
};