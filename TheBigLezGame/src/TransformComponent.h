#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class TransformComponent {
private:
	glm::mat4 matrix;
	glm::vec4 position;

	// Add all rotations, translations, etc and then use them in Render
	glm::vec4 rotation;
public:
	TransformComponent(glm::vec4 objectMatrix) {
		position = objectMatrix;
	};
	glm::vec3 getPosition();
	glm::mat4 getMatrix();
	void move(glm::vec3 position);
	void rotate(glm::vec3 rotation);
	void setView(glm::mat4 view);
};