#pragma once
#include "GameObject.h"
#include <iostream>
#include <string>

//Obstacle is a utility game object to be purely for collider representation, being neither a player, prop or enemy.
struct Obstacle : public GameObject
{
	struct Character
	{
		string file;
		string name;
	};

	Obstacle(Character character, std::string name, glm::vec3 startPos);
	Obstacle(std::string name, glm::vec3 startPos);
	~Obstacle();

	void update() override;

	std::string name;
	Character m_char;
};
