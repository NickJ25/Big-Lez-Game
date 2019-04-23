#include "RenderComponent.h"

// Load Standard Object
void RenderComponent::loadObject(const char* mesh_filename)
{
	//testModel = new Model(mesh_filename); // TEST
	m_objModel = new AnimModel();
	m_objModel->loadModel(mesh_filename);
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
	m_objModel->initShaders(newShader->getID());
}

void RenderComponent::setAnim(float s, float e)
{
	m_objModel->setAnimation(s, e);
}

void RenderComponent::setPaused(bool p)
{
	m_objModel->setPaused(p);
}

void RenderComponent::setPauseFrame(float p)
{
	m_objModel->setPauseFrame(p);
}

void RenderComponent::setStill(bool s)
{
	m_objModel->setStill(s);
}

bool RenderComponent::getPaused()
{
	return m_objModel->getPaused();
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
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "normals"), 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::transpose(glm::inverse(m_model)))));
	// Draw Items////////////////

	m_objModel->draw(m_currentShader->getID(), true);
	//testModel->Draw(*m_currentShader); // TEST
	glUseProgram(0);
	// End Draw Items////////////
	//mvStack.pop();
}
