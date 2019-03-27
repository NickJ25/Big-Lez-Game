#pragma once
#include "GameObject.h"

class CollisionComponent {
private:
	glm::vec3 centre;
	glm::vec3 scale;
	float halfWidth;
	float halfHeight; // Depth in 3D, Height in 2D
	float halfTrueHeight;

public:
	CollisionComponent(glm::vec3 pos, float hw, float hh, float th) : centre(pos), halfWidth(hw), halfHeight(hh), halfTrueHeight(th){}
	//CollisionComponent(glm::vec3 pos)

	void setCollider(glm::vec3 newPos);

	void moveCollider(glm::vec3 moveAmount);

	glm::vec3 getPos();
	glm::vec3 getScale();
	float getHW();
	float getHH();
	float getTH();


	//bool checkCollisions(GameObject* a, GameObject* b);
	//void checkCollisions(GameObject* a, GameObject* b, bool &x, bool &y, bool &z);
};