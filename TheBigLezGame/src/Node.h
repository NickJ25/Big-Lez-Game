#pragma once
#include <glm/vec3.hpp>

struct Node {

	Node(float size);

	glm::vec3 position;
	bool isBlocked = false;
	float fCost, gCost = 0, hCost = 0;

	float gridX, gridY;
	Node *parent;

	float getFCost()
	{
		fCost = gCost + hCost;
		return fCost;
	}
};