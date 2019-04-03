#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include "SOIL2/SOIL2.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Input.h"

class Image {
private:
	GLfloat backgroundCoords[12] = {
		// first triangle
		1.0f, -1.0f, 0.0f,  // bottom right
		1.0f,  1.0f, 0.0f,  // top right
		-1.0f,  1.0f, 0.0f,   // top left
		-1.0f, -1.0f, 0.0f,  // bottom left 
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
	int m_imgHeight, m_imgWidth;
	int m_Width, m_Height;
	unsigned char *m_image;
	GLuint m_VAO;
	GLuint m_VBO, m_VBO2, m_EBO;
	GLuint m_texture;


	glm::mat4 m_model = glm::mat4(1.0);
	glm::mat4 m_proj = glm::mat4(1.0);
	glm::mat4 m_view = glm::mat4(1.0);

	void init(unsigned char *image);
public:
	Image(const char* filename, glm::vec2 screenPos);
	Image(const char* filename, glm::vec2 screenPos, int width, int height);
	~Image();
	void translate(glm::vec2 position);
	void rotate(GLfloat radians);
	void scale(glm::vec2 scale);
	void draw();
};
