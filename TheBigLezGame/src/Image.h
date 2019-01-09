#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include "SOIL2/SOIL2.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Image {
private:
	GLfloat backgroundCoords[12] = {
		// first triangle
		 1.0f,  1.0f, 0.0f,  // top right
		 1.0f, -1.0f, 0.0f,  // bottom right
		-1.0f, -1.0f, 0.0f,  // top left 
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
	unsigned char *image;
	GLuint m_VAO;
	GLuint m_VBO, m_VBO2, m_EBO;
	GLuint m_texture;
	glm::mat4 m_rotation = glm::mat4(1.0);
public:
	Image(const char* filename);
	~Image();
	void rotate(GLfloat radians);
	void draw();
};
