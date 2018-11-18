#include "SpotLight.h"

void SpotLight::update()
{
	shaderID = objShader->getID();
	// ADJUST TO USER SHADERS PASSIN METHODS
	glUniform3f(glGetUniformLocation(shaderID, "light.ambient"), m_ambient.x, m_ambient.y, m_ambient.z);
	cout << "SPOTLIGHT :: light.ambient: " << glGetUniformLocation(shaderID, "light.ambient") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.diffuse"), m_diffuse.x, m_diffuse.y, m_diffuse.z);
	cout << "SPOTLIGHT :: light.diffuse: " << glGetUniformLocation(shaderID, "light.diffuse") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.specular"), m_specular.x, m_specular.y, m_specular.z);
	cout << "SPOTLIGHT :: light.specular: " << glGetUniformLocation(shaderID, "light.specular") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "light.constant"), constant);
	cout << "SPOTLIGHT :: light.constant: " << glGetUniformLocation(shaderID, "light.constant") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "light.linear"), linear);
	cout << "SPOTLIGHT :: light.linear: " << glGetUniformLocation(shaderID, "light.linear") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "light.quadratic"), quadratic);
	cout << "SPOTLIGHT :: light.quadratic: " << glGetUniformLocation(shaderID, "light.quadratic") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "light.cutOff"), m_cutOff);
	cout << "SPOTLIGHT :: light.cutOff: " << glGetUniformLocation(shaderID, "light.cutOff") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "light.outerCutOff"), m_outerCutOff);
	cout << "SPOTLIGHT :: light.outerCutOff: " << glGetUniformLocation(shaderID, "light.outerCutOff") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.position"), objPosition.x, objPosition.y, objPosition.z);
	cout << "SPOTLIGHT :: Light POS: " << glGetUniformLocation(shaderID, "light.position") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.direction"), m_direction.x, m_direction.y, m_direction.z);
	cout << "SPOTLIGHT :: Light POS: " << glGetUniformLocation(shaderID, "light.direction") << endl;
}
