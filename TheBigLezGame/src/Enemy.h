#pragma once
#pragma once
#include "GameObject.h"
#include "Shader.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <cmath>


class Enemy : public GameObject
{
public:
	struct Character {
		std::string name;
		std::string fileLocation;
		bool isLocked;
	};

	Enemy(Character character);
	~Enemy();

	//function to give its pathfinding movement
	void setPath(std::vector<glm::vec3> p ,bool outer);
	void setPathEnd(glm::vec3 p, bool outer);

	void getPlayerPosition(glm::vec3 p)
	{
		innerPathEnd = p;
	}

	void setTarget(Player* p)
	{
		target = p;
	}

	glm::vec3 getPathEnd()
	{
		return outerPathEnd;
	}

	bool getLocation()
	{
		return inside;
	}
	std::vector<glm::vec3> Enemy::getPath();

	void update() override;

	glm::vec3 rotation;
private:
	
	std::vector<glm::vec3> outerPath;
	std::vector<glm::vec3> innerPath;
	glm::vec3 outerPathEnd;
	glm::vec3 innerPathEnd;

	bool inside;
	bool outsideMovement;
	

	float velocity;

	Player* target;
};

