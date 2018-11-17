#pragma once
#include "Light.h"
class DirectionalLight : public Light {
private:
	glm::vec3 m_direction;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	GLuint shaderID;

public:
	DirectionalLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(position),
		m_direction(direction), m_ambient(ambient), m_diffuse(diffuse), m_specular(specular){

	};

	void update() override;
};