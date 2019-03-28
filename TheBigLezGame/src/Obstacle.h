#pragma once
#include "GameObject.h"
#include <iostream>
#include <string>

struct Obstacle : public GameObject
{
	struct Character
	{
		string file;
		string name;
	};

	Obstacle(Character character, std::string name, glm::vec3 startPos);
	~Obstacle();

	void update() override;

	std::string name;
	Character m_char;
};

// Make camera unique
// Make array to hold multiple players
