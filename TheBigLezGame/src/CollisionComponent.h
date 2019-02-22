#pragma once
#include "GameObject.h"

class CollisionComponent {
private:
	glm::vec3 centre;
	glm::vec3 scale;
	float halfWidth;
	float halfHeight;

public:
	CollisionComponent(glm::vec3 pos, glm::vec3 s, float hw, float hh) : centre(pos), scale(s), halfWidth(hw), halfHeight(hh)
	{

	}

	glm::vec3 getPos();
	glm::vec3 getScale();
	float getHW();
	float getHH();


	//bool checkCollisions(GameObject* a, GameObject* b);
	//void checkCollisions(GameObject* a, GameObject* b, bool &x, bool &y, bool &z);
};