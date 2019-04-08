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

void TransformComponent::resetMatrix()
{
	m_matrix = glm::mat4(1.0f);
}

void TransformComponent::setMatrix(glm::mat4 newMat)
{
	m_matrix = newMat;
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void TransformComponent::setPosition(glm::vec3 newPos)
{
	//cout << "---------------- Matrix 1 ----------------" << endl;
	//cout << m_matrix[0][0] << " " << m_matrix[1][0] << " " << m_matrix[2][3] << " " << m_matrix[3][0] << endl;
	//cout << m_matrix[0][1] << " " << m_matrix[1][1] << " " << m_matrix[2][3] << " " << m_matrix[3][1] << endl;
	//cout << m_matrix[0][2] << " " << m_matrix[1][2] << " " << m_matrix[2][3] << " " << m_matrix[3][2] << endl;
	//cout << m_matrix[0][3] << " " << m_matrix[1][3] << " " << m_matrix[2][3] << " " << m_matrix[3][3] << endl;
	//cout << "------------------------------------------" << endl;
	m_matrix = glm::translate(m_matrix, (this->getPosition() *= -1.0f));
	cout << this->getPosition().x << " " << this->getPosition().y << " " << this->getPosition().z << endl;
	//cout << getPosition().x << " " << getPosition().y << " " << getPosition().z << endl;
	//m_matrix = glm::translate(m_matrix, -getPosition());
	//cout << getPosition().x << " " << getPosition().y << " " << getPosition().z << endl;
	m_matrix = glm::translate(m_matrix, newPos);
	//cout << getPosition().x << " " << getPosition().y << " " << getPosition().z << endl;
	//cout << endl;
}


void TransformComponent::move(glm::vec3 position)
{
	m_matrix = glm::translate(m_matrix, position);
	m_position += position;
}

void TransformComponent::rotate(GLfloat radians, glm::vec3 rotation)
{
	glm::vec3 tempVec = this->getPosition();
	//cout << "first pos: " << this->getPosition().x << " " << this->getPosition().y << " " << this->getPosition().z <<  endl;
	m_matrix = glm::translate(m_matrix, (this->getPosition() * -1.0f));
	//cout << "second pos: " << this->getPosition().x << " " << this->getPosition().y << " " << this->getPosition().z << endl;
	m_matrix = glm::rotate(m_matrix, glm::radians(radians), rotation);
	//cout << "tempVec: " << tempVec.x << " " << tempVec.y << " " << tempVec.z << endl;
	m_matrix = glm::translate(m_matrix, tempVec);
	//cout << "third pos: " << this->getPosition().x << " " << this->getPosition().y << " " << this->getPosition().z << "\n"<< endl;
}

glm::vec3 TransformComponent::getRotation()
{
	return glm::normalize(glm::column(m_matrix, 0));
}

void TransformComponent::scale(glm::vec3 scale)
{
	glm::vec3 tempVec = this->getPosition();
	m_matrix = glm::translate(m_matrix, (this->getPosition()));
	m_matrix = glm::scale(m_matrix, scale);
	m_matrix = glm::translate(m_matrix, tempVec);
}
