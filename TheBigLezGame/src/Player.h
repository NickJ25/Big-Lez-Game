#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Weapon.h"
//#include "Shader.h"
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

	Player(Character character, glm::vec3 startPos);
	~Player();

	void playAnimation();
	Camera* getCamera();
	void update() override;

private:
	Character selectCharacter;
	Camera* m_playerCamera;
	Weapon* m_playerInventory[];

};

// Make camera unique
// Make array to hold multiple players
