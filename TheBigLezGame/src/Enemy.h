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

	Player* getTarget()
	{
		return target;
	}

	glm::vec3 getPathEnd(bool outer)
	{
		if (outer == true)
			return outerPathEnd;
		else
			return innerPathEnd;
	}

	bool getLocation()
	{
		return inside;
	}
	std::vector<glm::vec3> getPath();

	void update() override;

	glm::vec3 rotation;

	glm::vec3 getCurrentTargetPosition()
	{
		return currentTargetPosition;
	}

	void setCurrentTargetPosition(glm::vec3 p)
	{
		currentTargetPosition = p;
	}
private:
	
	std::vector<glm::vec3> outerPath;
	std::vector<glm::vec3> innerPath;
	glm::vec3 outerPathEnd;
	glm::vec3 innerPathEnd;

	bool inside;
	bool outsideMovement;
	int jumpingCounter;
	

	float velocity;

	Player* target;
	glm::vec3 currentTargetPosition;
};

