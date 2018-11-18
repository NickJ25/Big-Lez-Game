#include "Camera.h"

glm::mat4 Camera::lookAtMat()
{
	return glm::lookAt(m_position, m_position - m_front ,m_up);
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
		//SDL_SetRelativeMouseMode(SDL_TRUE);
		int xpos, ypos;
		
		SDL_GetMouseState(&xpos, &ypos); /////////////////////////////////////////LIMITED, REACHES END OF SCREEN

		if (firstCamLoad) {
			lastOffsetX = (float)xpos;
			lastOffsetY = (float)ypos;
			firstCamLoad = false;
		}
		
		mouseOffsetX = (float)xpos - lastOffsetX;
		mouseOffsetY =  (float)ypos - lastOffsetY;
		lastOffsetX = (float)xpos;
		lastOffsetY = (float)ypos;

		this->m_yaw += mouseOffsetX *this->m_mouseSensitivity;
		this->m_pitch += mouseOffsetY *this->m_mouseSensitivity;
		//cout << m_yaw << " " << m_pitch << endl;
		//cout << "Yaw: " << m_yaw << " | Pitch: " << m_pitch << " | MX: " << xpos << " | MY: " << ypos <<endl;

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
