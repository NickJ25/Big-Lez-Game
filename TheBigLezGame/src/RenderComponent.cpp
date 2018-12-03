#include "RenderComponent.h"

// Load Standard Object
void RenderComponent::loadObject(const char* mesh_filename)
{
	testModel = new Model(mesh_filename); // TEST
}

// Load Animated Object
void RenderComponent::loadAnimObject(const char* mesh_filename)
{

}

void RenderComponent::depthMask(GLboolean mode)
{
	m_depthMask = mode;
}

void RenderComponent::cullFace(GLenum mode)
{
	m_cullMode = mode;
}

void RenderComponent::setView(glm::mat4 view)
{
	m_view = view;
}

void RenderComponent::setDrawMatrix(glm::mat4 matrix)
{
	m_model = matrix;
}

void RenderComponent::textureOverride(GLuint textureID)
{
	m_overrideTexture = textureID;
}

void RenderComponent::changeShader(Shader* newShader)
{
	m_currentShader = newShader;
}

void RenderComponent::Draw()
{
	// Select Modes
	glCullFace(m_cullMode);
	glDepthMask(m_depthMask);
	glUseProgram(m_currentShader->getID());

	int shaderID = m_currentShader->getID(); // TEMP
	if(m_overrideTexture == NULL) glBindTexture(m_currentShader->getID(), m_overrideTexture); // Override textures
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(m_model));
	//cout << "Projection: " << glGetUniformLocation(shaderID, "projection") << endl; // TEMP
	//cout << "Model: " << glGetUniformLocation(shaderID, "model") << endl; // TEMP
	//cout << "View: " << glGetUniformLocation(shaderID, "view") << endl; // TEMP
	// Draw Items////////////////
	testModel->Draw(*m_currentShader); // TEST
	// End Draw Items////////////
	//mvStack.pop();
	//m_currentShader->Pass("projection", );
	//m_currentShader->Pass("model", );
	//m_currentShader->Pass("view", );
}
