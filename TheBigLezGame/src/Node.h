#pragma once
#include <glm/vec3.hpp>

struct Node {

	Node();

	glm::vec3 position;
	bool isBlocked = false;

};