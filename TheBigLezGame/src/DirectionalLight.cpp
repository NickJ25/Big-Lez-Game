#include "DirectionalLight.h"

void DirectionalLight::update()
{
	shaderID = objShader->getID();
	glUseProgram(shaderID);
	// ADJUST TO USER SHADERS PASSIN METHODS
	glUniform3f(glGetUniformLocation(shaderID, "dirLight.direction"), m_direction.x, m_direction.y, m_direction.z);
	glUniform3f(glGetUniformLocation(shaderID, "dirLight.ambient"), m_ambient.x, m_ambient.y, m_ambient.z);
	glUniform3f(glGetUniformLocation(shaderID, "dirLight.diffuse"), m_diffuse.x, m_diffuse.y, m_diffuse.z);
	glUniform3f(glGetUniformLocation(shaderID, "dirLight.specular"), m_specular.x, m_specular.y, m_specular.z);
}
