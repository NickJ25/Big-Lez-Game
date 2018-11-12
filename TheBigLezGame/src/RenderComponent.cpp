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
	testModel->Draw(*m_currentShader); // TEST
	// Do Transformations

	// DRAW

	// Repeat
}
