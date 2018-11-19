#include "PointLight.h"

void PointLight::update()
{
	shaderID = objShader->getID();
	// ADJUST TO USER SHADERS PASSIN METHODS
	glUniform3f(glGetUniformLocation(shaderID, "pointLights[0].ambient"), m_ambient.x, m_ambient.y, m_ambient.z);
	cout << "POINTLIGHT :: Light Ambient: " << glGetUniformLocation(shaderID, "pointLights[0].ambient") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "pointLights[0].diffuse"), m_diffuse.x, m_diffuse.y, m_diffuse.z);
	cout << "POINTLIGHT :: Light diffuse: " << glGetUniformLocation(shaderID, "pointLights[0].diffuse") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "pointLights[0].specular"), m_specular.x, m_specular.y, m_specular.z);
	cout << "POINTLIGHT :: Light specular: " << glGetUniformLocation(shaderID, "pointLights[0].specular") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "pointLights[0].constant"), constant);
	cout << "POINTLIGHT :: Light constant: " << glGetUniformLocation(shaderID, "pointLights[0].constant") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "pointLights[0].linear"), linear);
	cout << "POINTLIGHT :: Light linear: " << glGetUniformLocation(shaderID, "pointLights[0].linear") << endl;
	glUniform1f(glGetUniformLocation(shaderID, "pointLights[0].quadratic"), quadratic);
	cout << "POINTLIGHT :: Light quadratic: " << glGetUniformLocation(shaderID, "pointLights[0].quadratic") << endl;
	glUniform3f(glGetUniformLocation(shaderID, "pointLights[0].position"), objPosition.x, objPosition.y, objPosition.z);
	cout << "POINTLIGHT :: Light POS: " << glGetUniformLocation(shaderID, "pointLights[0].position") << endl;
}
