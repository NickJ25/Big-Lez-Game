#include "Camera.h"

void Camera::follow(glm::vec3 &objPosition)
{
	m_followPos = &objPosition;
}

void Camera::unfollow()
{
	m_followPos = nullptr;
}

void Camera::update()
{
	if (m_followPos != nullptr) {
		m_position = *m_followPos;
	}
	if(m_camType = DYNAMIC){
		
	}
}
