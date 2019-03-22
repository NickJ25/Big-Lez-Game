#pragma once
#include "GameObject.h"
#include <iostream>
#include <string>

struct Obstacle : public GameObject
{

	Obstacle(std::string name, glm::vec3 startPos);
	~Obstacle();

	void update() override;

	std::string name;
};

// Make camera unique
// Make array to hold multiple players
