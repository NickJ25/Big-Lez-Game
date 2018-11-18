#include "TransformComponent.h"

glm::vec3 TransformComponent::getPosition()
{
	return m_position;
}

glm::mat4 TransformComponent::getMatrix()
{
	return m_matrix;
}

void TransformComponent::move(glm::vec3 position)
{
	m_matrix = glm::translate(m_matrix, position);
}

void TransformComponent::rotate(GLfloat radians, glm::vec3 rotation)
{
	m_matrix = glm::rotate(m_matrix, glm::radians(radians), rotation);
}

void TransformComponent::scale(glm::vec3 scale)
{
	m_matrix = glm::scale(m_matrix, scale);
}
