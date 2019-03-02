#pragma once
#pragma once
#include "GameObject.h"
#include "Shader.h"

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

	glm::vec3 getPathEnd()
	{
		return outerPathEnd;
	}

	std::vector<glm::vec3> Enemy::getPath();

	void update() override;

private:
	
	std::vector<glm::vec3> outerPath;
	std::vector<glm::vec3> innerPath;
	glm::vec3 outerPathEnd;
	glm::vec3 innerPathEnd;

	float velocity;

};

