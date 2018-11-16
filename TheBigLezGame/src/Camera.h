#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
enum Camera_Type
{
	STATIC,
	DYNAMIC,
};

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_up;
	glm::vec3 m_right;
	Camera_Type m_camType;

	// Rotation Angles (Eular)
	GLfloat m_yaw; // Left - Right
	GLfloat m_pitch; // Up - Down

	glm::vec3* m_followPos;
	bool isFollowing = false;
	bool isLookAt = false;
public:
	Camera();
	~Camera() {
		delete m_followPos;
	}
	void lookAt(GameObject object);
	//void lookAt(0);
	void follow(glm::vec3 &position);
	void unfollow();

	void update();
};