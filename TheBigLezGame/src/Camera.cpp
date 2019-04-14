#include "Camera.h"

glm::mat4 Camera::lookAtMat()
{
	return glm::lookAt(m_position, m_position - m_front, m_up); // + ?
}

glm::vec3 Camera::getCameraFront()
{
	return m_front;
}

glm::vec3 Camera::getCameraPos()
{
	return m_position;
}

void Camera::setCameraPos(glm::vec3 newPos)
{
	m_position = newPos;
}

glm::vec3 Camera::getFront()
{
	return m_front;
}

glm::vec3 Camera::getRight()
{
	return glm::vec3();
}

void Camera::follow(glm::vec3 &objPosition)
{
	m_position = objPosition;
}

void Camera::unfollow()
{
	m_followPos = nullptr;
}

void Camera::update()
{
	// Different types of camera movement
	switch (m_camType) {
	case FREECAM: // Aka noclip (Uses keyboard)
	{
		if (Input::keyboard1.keys[GLFW_KEY_W]) {
			m_position -= m_front * 1.0f;
		}
		if (Input::keyboard1.keys[GLFW_KEY_S]) {
			m_position += m_front * 1.0f;
		}
		if (Input::keyboard1.keys[GLFW_KEY_A]) {
			m_position += glm::normalize(glm::cross(m_front, m_up)) * 1.0f;
		}
		if (Input::keyboard1.keys[GLFW_KEY_D]) {
			m_position -= glm::normalize(glm::cross(m_front, m_up)) * 1.0f;
		}

		if (Input::keyboard1.keys[GLFW_KEY_LEFT_SHIFT]) {
			m_position -= glm::vec3(0.0f, 1.0f, 0.0f);
		}
		if (Input::keyboard1.keys[GLFW_KEY_SPACE]) {
			m_position += glm::vec3(0.0f, 1.0f, 0.0f);
		}
	}
	case KEYBOARD: // Keyboard Usage
	{
		// Keyboard looking, keeps mouse 'locked' into centre
		float xpos, ypos;
		xpos = Input::mouse1.current_Xpos;
		ypos = Input::mouse1.current_Ypos;

		if (firstCamLoad) {
			lastOffsetX = (float)xpos;
			lastOffsetY = (float)ypos;
			firstCamLoad = false;
		}

		mouseOffsetX = (float)xpos - lastOffsetX;
		mouseOffsetY = lastOffsetY - (float)ypos;
		lastOffsetX = (float)xpos;
		lastOffsetY = (float)ypos;

		this->m_yaw += (mouseOffsetX *= this->m_mouseSensitivity);
		this->m_pitch += (mouseOffsetY *= this->m_mouseSensitivity);
		break;
	}
	case CONTROLLER: // Controller Usage
	{
		// Controller looking
		float xpos, ypos;
		xpos = Input::controller1.rightThumb.x;
		ypos = Input::controller1.rightThumb.y;

		this->m_yaw += ((xpos * 9) * this->m_mouseSensitivity);
		this->m_pitch += ((-ypos * 8) * this->m_mouseSensitivity);
		break;
	}
	}

	// Prevent m_yaw value from overflowing
	if (m_yaw > 360) m_yaw = 0;
	if (m_yaw < 0) m_yaw = 360;

	// Lock pitch so player can 'flip' camera/ look too far up or down
	if (this->m_pitch > 89.0f)
	{
		this->m_pitch = 89.0f;
	}

	if (this->m_pitch < -89.0f)
	{
		this->m_pitch = -89.0f;
	}

	// Recalculate front and right
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) *cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) *cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, m_up));
}

GLfloat Camera::getYaw()
{
	return m_yaw;
}
