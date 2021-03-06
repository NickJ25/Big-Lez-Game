#include "SpotLight.h"

void SpotLight::update()
{
	shaderID = objShader->getID();
	// ADJUST TO USER SHADERS PASSIN METHODS
	glUniform3f(glGetUniformLocation(shaderID, "light.ambient"), m_ambient.x, m_ambient.y, m_ambient.z);
	glUniform3f(glGetUniformLocation(shaderID, "light.diffuse"), m_diffuse.x, m_diffuse.y, m_diffuse.z);
	glUniform3f(glGetUniformLocation(shaderID, "light.specular"), m_specular.x, m_specular.y, m_specular.z);
	glUniform1f(glGetUniformLocation(shaderID, "light.constant"), constant);
	glUniform1f(glGetUniformLocation(shaderID, "light.linear"), linear);
	glUniform1f(glGetUniformLocation(shaderID, "light.quadratic"), quadratic);
	glUniform1f(glGetUniformLocation(shaderID, "light.cutOff"), m_cutOff);
	glUniform1f(glGetUniformLocation(shaderID, "light.outerCutOff"), m_outerCutOff);
	glUniform3f(glGetUniformLocation(shaderID, "light.position"), objPosition.x, objPosition.y, objPosition.z);
	glUniform3f(glGetUniformLocation(shaderID, "light.direction"), m_direction.x, m_direction.y, m_direction.z);
}
