#pragma once
#pragma once
#include "Light.h"
class SpotLight : public Light {
private:
	// Attenuation values
	float m_cutOff;
	float m_outerCutOff;  // values to determine the spotlight size

	float constant;
	float linear;
	float quadratic;  

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_direction;

	GLuint shaderID;

public:
	SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 attenuation, float cutOff, float outerCutOff) : Light(position),
		m_direction(direction), m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), constant(attenuation.x), linear(attenuation.y), quadratic(attenuation.z), m_cutOff(cutOff), m_outerCutOff(outerCutOff) {

	};

	void update() override;
};