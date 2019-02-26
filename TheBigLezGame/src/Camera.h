#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Input.h"
enum Camera_Type
{
	STATIC,
	DYNAMIC,
	FREECAM,
};

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_right;
	glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera_Type m_camType;

	GLfloat m_mouseSensitivity = 0.25f;

	// Rotation Angles (Eular)
	GLfloat m_yaw; // Left - Right
	GLfloat m_pitch; // Up - Down
	GLfloat mouseOffsetX, mouseOffsetY; //The Mouse Movements 
	GLfloat lastOffsetX = 640, lastOffsetY = 360;
	bool firstCamLoad = true;

	// Attributes
	glm::vec3 rightDirection = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

	glm::vec3* m_followPos;
	bool isFollowing = false;
	bool isLookAt = false;
public:
	Camera(glm::vec3 position, Camera_Type camType) : m_position(position), m_camType(camType) {};
	~Camera() {
		delete m_followPos;
	}
	glm::mat4 lookAtMat();
	glm::vec3 getCameraFront();
	glm::vec3 getCameraPos();
	glm::vec3 getRotation();
	GLfloat getYaw();
	//void lookAt(GameObject object);
	//void lookAt(0);
	void follow(glm::vec3 &position);
	void unfollow();

	void update();
};