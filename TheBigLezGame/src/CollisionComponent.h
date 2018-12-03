#pragma once
#include "GameObject.h"
class CollisionComponent {
private:
	glm::vec3 m_collisionSize;
public:
	CollisionComponent(glm::vec3 collisionSize) : m_collisionSize(collisionSize) {

	}

	glm::vec3 getCollision();

	//bool checkCollisions(GameObject* a, GameObject* b);
	//void checkCollisions(GameObject* a, GameObject* b, bool &x, bool &y, bool &z);
};