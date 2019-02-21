#pragma once
#pragma once
#include "GameObject.h"
#include "Shader.h"
#include <iostream>
#include <string>

class Enemy : public GameObject
{
public:
	struct Character {
		std::string name;
		std::string fileLocation;
		bool isLocked;
	};

	Enemy(Character character, glm::vec3 startPos);
	~Enemy();

	//function to give its pathfinding movement

	void update() override;

private:

};

