#pragma once
#include "GameObject.h"

class CollisionComponent {
private:
	glm::vec3 centre;
	glm::vec3 scale;
	float halfWidth;
	float halfHeight;

public:
	CollisionComponent(glm::vec3 pos, float hw, float hh) : centre(pos), halfWidth(hw), halfHeight(hh)
	{

	}

	void setScale(glm::vec3 newScale);

	void setCollider(glm::vec3 newPos);

	void moveCollider(glm::vec3 moveAmount);

	glm::vec3 getPos();
	glm::vec3 getScale();
	float getHW();
	float getHH();


	//bool checkCollisions(GameObject* a, GameObject* b);
	//void checkCollisions(GameObject* a, GameObject* b, bool &x, bool &y, bool &z);
};