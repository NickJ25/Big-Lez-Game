#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"glm\gtc\matrix_access.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GL/glew.h"

using namespace std;

class TransformComponent {
private:
	glm::mat4 m_matrix = glm::mat4(1.0);
	glm::vec3 m_position;


	// Add all rotations, translations, etc and then use them in Render
	glm::vec4 rotation;
public:
	TransformComponent(glm::vec4 objectMatrix) {

		m_position = glm::vec3(objectMatrix.x, objectMatrix.y, objectMatrix.z);
	};
	glm::vec3 getPosition();
	glm::mat4 getMatrix();
	void resetMatrix();
	void setMatrix(glm::mat4 newMat);
	void setPosition(glm::vec3 newPos);
	void move(glm::vec3 position);
	void rotate(GLfloat radians, glm::vec3 rotation);
	void scale(glm::vec3 scale);
	void setView(glm::mat4 view);

	glm::vec3 getRotation();
};