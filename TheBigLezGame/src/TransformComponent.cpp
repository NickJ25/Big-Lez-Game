#include "TransformComponent.h"

#include <iostream>

glm::vec3 TransformComponent::getPosition()
{
	glm::vec3 tempPos = glm::vec3(m_matrix[0][3], m_matrix[1][3], m_matrix[2][3]);
	return tempPos;
}

glm::mat4 TransformComponent::getMatrix()
{
	return m_matrix;
}

void TransformComponent::setPosition(glm::vec3 newPos)
{
	m_matrix[0][3] = newPos.x;
	m_matrix[1][3] = newPos.y;
	m_matrix[2][3] = newPos.z;
}


void TransformComponent::move(glm::vec3 position)
{
	m_matrix = glm::translate(m_matrix, position);
}

void TransformComponent::rotate(GLfloat radians, glm::vec3 rotation)
{
	glm::vec3 tempVec = this->getPosition();
	m_matrix = glm::translate(m_matrix, (this->getPosition()));
	m_matrix = glm::rotate(m_matrix, glm::radians(radians), rotation);
	m_matrix = glm::translate(m_matrix, tempVec);
}

void TransformComponent::scale(glm::vec3 scale)
{
	glm::vec3 tempVec = this->getPosition();
	m_matrix = glm::translate(m_matrix, (this->getPosition()));
	m_matrix = glm::scale(m_matrix, scale);
	m_matrix = glm::translate(m_matrix, tempVec);
}
