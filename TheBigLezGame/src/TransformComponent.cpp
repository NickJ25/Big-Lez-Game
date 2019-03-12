#include "TransformComponent.h"

#include <iostream>

glm::vec3 TransformComponent::getPosition()
{
	glm::vec3 tempPos = glm::vec3(m_matrix[3][0], m_matrix[3][1], m_matrix[3][2]);
	return tempPos;
}

glm::mat4 TransformComponent::getMatrix()
{
	return m_matrix;
}

void TransformComponent::setMatrix(glm::mat4 newMat)
{
	m_matrix = newMat;
}

void TransformComponent::setPosition(glm::vec3 newPos)
{
	//cout << "---------------- Matrix 1 ----------------" << endl;
	//cout << m_matrix[0][0] << " " << m_matrix[1][0] << " " << m_matrix[2][3] << " " << m_matrix[3][0] << endl;
	//cout << m_matrix[0][1] << " " << m_matrix[1][1] << " " << m_matrix[2][3] << " " << m_matrix[3][1] << endl;
	//cout << m_matrix[0][2] << " " << m_matrix[1][2] << " " << m_matrix[2][3] << " " << m_matrix[3][2] << endl;
	//cout << m_matrix[0][3] << " " << m_matrix[1][3] << " " << m_matrix[2][3] << " " << m_matrix[3][3] << endl;
	//cout << "------------------------------------------" << endl;
	m_matrix = glm::translate(m_matrix, -this->getPosition());
	cout << this->getPosition().x << " " << this->getPosition().y << " " << this->getPosition().z << endl;
	m_matrix = glm::translate(m_matrix, newPos);
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
