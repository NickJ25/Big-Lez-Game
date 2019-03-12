#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Weapon.h"
#include "Text.h"
#include <iostream>
#include <string>

class Player : public GameObject
{
public:
	struct Character {
		std::string name;
		std::string fileLocation;
		bool isLocked;
		GLint health;
		GLint walkSpeed;
	};

	Player(Character character, glm::vec3 startPos);
	~Player();

	void playAnimation();
	Camera* getCamera();
	void update() override;
	
	Character getCharacter()
	{
		return selectCharacter;
	}

private:
	Character selectCharacter;
	Camera* m_playerCamera;
	Text* m_charLabel;
	//Weapon* m_playerInventory[];

	GLfloat prevYaw, currentYaw;

	GLuint m_health;

	glm::vec3 colourTemp = glm::vec3(0.2, 0.4, 0.5);

};

// Make camera unique
// Make array to hold multiple players
