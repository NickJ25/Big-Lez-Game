#pragma once
#include "GameObject.h"
#include "Shader.h"
#include <iostream>
#include <string>

class Player : public GameObject
{
public:
	struct Character {
		std::string name;
		std::string fileLocation;
		bool isLocked;
	};

	Player(Character character);
	~Player();

	void update() override;

private:
	Character selectCharacter;
};

// Make camera unique
// Make array to hold multiple players
