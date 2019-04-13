#pragma once
#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	GLuint ID;
	
public:
	Shader(const GLchar *vertexPath, const GLchar * geometryPath, const GLchar *fragmentPath);
	GLuint getID();
	void use();
};

