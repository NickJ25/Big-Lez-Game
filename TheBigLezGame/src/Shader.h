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
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	GLuint getID();
	void use();

	template <typename T>
	void Pass(const char* location, T value);
};

template<typename T>
inline void Shader::Pass(const char * location, T value)
{
	GLuint uniformIndex = glGetUniformLocation(ID, location);
	if (uniformIndex == -1) {
		std::cout << "ERROR::SHADER::PASS_LOCATION_NOT_FOUND" << std::endl;
		
	}
	else {

		if (is_same<T, float>::value) {
			glUniform1f(uniformIndex, value);
		}
		else if (is_same<T, int>::value) {
			glUniform1i(uniformIndex, value);
		}
		//else if (is_same<T, glm::vec2>::value) {
		//	glUniform2fv(uniformIndex, 1, value);
		//}
		//else if (is_same<T, glm::vec3>::value) {
		//	glUniform3fv(uniformIndex, 1, value);
		//}
		//else if (is_same<T, glm::vec4>::value) {
		//	glUniform4fv(uniformIndex, 1, value);
		//}
		else {
			std::cout << "ERROR::SHADER::PASS_TYPE_NOT_RECOGNISED" << std::endl;
		}

	}
}
