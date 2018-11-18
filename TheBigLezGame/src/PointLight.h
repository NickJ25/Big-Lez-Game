#pragma once
#include "Light.h"
class PointLight : public Light {
private:

	// Attenuation values
	float constant;
	float linear;
	float quadratic;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	GLuint shaderID;
public:
	PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 attenuation) : Light(position),
		 m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), constant(attenuation.x), linear(attenuation.y), quadratic(attenuation.z) {

	};

	void update() override;
};
