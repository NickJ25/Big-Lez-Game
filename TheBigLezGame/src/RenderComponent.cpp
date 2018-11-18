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

	int shaderID = m_currentShader->getID();
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	cout << "Projection: " << glGetUniformLocation(shaderID, "projection") << endl;
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
	cout << "View: " << glGetUniformLocation(shaderID, "view") << endl;
	glm::mat4 i(1.0);
	//i = glm::translate(i, glm::vec3(0.0, 5.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(m_model));
	cout << "Model: " << glGetUniformLocation(shaderID, "model") << endl;
	//mvStack.push(i);
	//mvStack.top() = m_view;
	//mvStack.top() = mvStack.top() * m_model;
	// Draw Items////////////////
	testModel->Draw(*m_currentShader); // TEST
	// End Draw Items////////////
	//mvStack.pop();
	//m_currentShader->Pass("projection", );
	//m_currentShader->Pass("model", );
	//m_currentShader->Pass("view", );


	// Do Transformations

	// DRAW

	// Repeat
}
