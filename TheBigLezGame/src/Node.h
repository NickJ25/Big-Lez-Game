#pragma once
#include <glm/vec3.hpp>

struct Node {

	Node(float size);

	glm::vec3 position;
	bool isBlocked = false;
	float fCost, gCost, hCost;
};