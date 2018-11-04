#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class TransformComponent {
private:
	glm::mat4 matrix;
public:
	TransformComponent(glm::mat4 objectMatrix) {
		matrix = objectMatrix;
	};
	glm::vec3 getPosition();
	glm::mat4 getMatrix();
	void move(glm::vec3 position);
	void rotate(glm::vec3 rotation);
	void setView(glm::mat4 view);
};