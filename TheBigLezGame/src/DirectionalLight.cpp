#include "DirectionalLight.h"

void DirectionalLight::update()
{
	shaderID = objShader->getID();
	// ADJUST TO USER SHADERS PASSIN METHODS
	glUniform3f(glGetUniformLocation(shaderID, "light.ambient"), m_ambient.x, m_ambient.y, m_ambient.z);
	cout << "Light Ambient: " << glGetUniformLocation(shaderID, "light.ambient") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.diffuse"), m_diffuse.x, m_diffuse.y, m_diffuse.z);
	cout << "Light diffuse: " << glGetUniformLocation(shaderID, "light.diffuse") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.specular"), m_specular.x, m_specular.y, m_specular.z);
	cout << "Light specular: " << glGetUniformLocation(shaderID, "light.specular") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.direction"), m_direction.x, m_direction.y, m_direction.z);
	cout << "Light direction: " << glGetUniformLocation(shaderID, "light.direction") << endl;
}
