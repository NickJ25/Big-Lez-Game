#include "PointLight.h"

void PointLight::update()
{
	shaderID = objShader->getID();
	// ADJUST TO USER SHADERS PASSIN METHODS
	glUniform3f(glGetUniformLocation(shaderID, "light.ambient"), m_ambient.x, m_ambient.y, m_ambient.z);
	cout << "POINTLIGHT :: Light Ambient: " << glGetUniformLocation(shaderID, "light.ambient") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.diffuse"), m_diffuse.x, m_diffuse.y, m_diffuse.z);
	cout << "POINTLIGHT :: Light diffuse: " << glGetUniformLocation(shaderID, "light.diffuse") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.specular"), m_specular.x, m_specular.y, m_specular.z);
	cout << "POINTLIGHT :: Light specular: " << glGetUniformLocation(shaderID, "light.specular") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "light.constant"), constant);
	cout << "POINTLIGHT :: Light constant: " << glGetUniformLocation(shaderID, "light.constant") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "light.linear"), linear);
	cout << "POINTLIGHT :: Light linear: " << glGetUniformLocation(shaderID, "light.linear") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "light.quadratic"), quadratic);
	cout << "POINTLIGHT :: Light quadratic: " << glGetUniformLocation(shaderID, "light.quadratic") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "light.position"), objPosition.x, objPosition.y, objPosition.z);
	cout << "POINTLIGHT :: Light POS: " << glGetUniformLocation(shaderID, "light.position") << endl;
}
