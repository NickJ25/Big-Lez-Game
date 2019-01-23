#include "Camera.h"

glm::mat4 Camera::lookAtMat()
{
	return glm::lookAt(m_position, m_position - m_front ,m_up); // + ?
}

glm::vec3 Camera::getCameraFront()
{
	return m_front;
}

glm::vec3 Camera::getCameraPos()
{
	return m_position;
}

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
		int xpos, ypos;
		
		xpos = Input::mouse1.current_Xpos;
		ypos = Input::mouse1.current_Ypos;

		if (firstCamLoad) { // Add start position for camera?
			lastOffsetX = (float)xpos;
			lastOffsetY = (float)ypos;
			firstCamLoad = false;
		}

		mouseOffsetX = (float)xpos - lastOffsetX;
		mouseOffsetY = lastOffsetY - (float)ypos;
		lastOffsetX = (float)xpos;
		lastOffsetY = (float)ypos;

		this->m_yaw += mouseOffsetX *= this->m_mouseSensitivity;
		this->m_pitch += mouseOffsetY *= this->m_mouseSensitivity;


		if (this->m_pitch > 89.0f)
		{
			this->m_pitch = 89.0f;
		}

		if (this->m_pitch < -89.0f)
		{
			this->m_pitch = -89.0f;
		}
		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(front);

	}
}
