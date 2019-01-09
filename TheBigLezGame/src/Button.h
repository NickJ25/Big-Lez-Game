#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include "SOIL2/SOIL2.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "MenuState.h"

class Button {
private:
	float m_width, m_height;
	glm::vec2 m_position;
	std::string m_text;
	glm::mat4 m_translation = glm::mat4(1.0);

	GLfloat backgroundCoords[12] = {
		// first triangle
		 1.0f,  1.0f, 0.0f,  // top right
		 1.0f, -0.4f, 0.0f,  // bottom right
		-1.0f, -0.4f, 0.0f,  // bottom left 
		-1.0f,  1.0f, 0.0f   // top left
	};

	GLfloat textureCoords[8] = {
		1.0f, 1.0f, // top left
		1.0f, 0.0f, // top right
		0.0f, 0.0f, // bottom left
		0.0f, 1.0f, // bottom right
	};

	unsigned int indices[6] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	Shader* imageShader;

	int height, width;

	GLuint m_VAO;
	GLuint m_VBO, m_VBO2, m_EBO;
	GLuint m_texNormal, m_texHover, m_texClick;
	GLuint imageGenerating(GLuint textureID, const char* filename);
	// Add audio for hoovering over the button
public:
	Button(glm::vec2 position, std::string button_text); // ,MenuState* destination
	~Button();
	void update();
	void draw();
};