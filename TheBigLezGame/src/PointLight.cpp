#include "PointLight.h"

void PointLight::update()
{
	shaderID = objShader->getID();
	// ADJUST TO USER SHADERS PASSIN METHODS
	glUniform3f(glGetUniformLocation(shaderID, "pointLights[0].ambient"), m_ambient.x, m_ambient.y, m_ambient.z);
	glUniform3f(glGetUniformLocation(shaderID, "pointLights[0].diffuse"), m_diffuse.x, m_diffuse.y, m_diffuse.z);
	glUniform3f(glGetUniformLocation(shaderID, "pointLights[0].specular"), m_specular.x, m_specular.y, m_specular.z);
	glUniform1f(glGetUniformLocation(shaderID, "pointLights[0].constant"), constant);
	glUniform1f(glGetUniformLocation(shaderID, "pointLights[0].linear"), linear);
	glUniform1f(glGetUniformLocation(shaderID, "pointLights[0].quadratic"), quadratic);
	glUniform3f(glGetUniformLocation(shaderID, "pointLights[0].position"), objPosition.x, objPosition.y, objPosition.z);
}
