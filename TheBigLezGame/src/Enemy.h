#define GLM_ENABLE_EXPERIMENTAL
#pragma once
#include "GameObject.h"
#include "Shader.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <cmath>

#include "glm/gtx/vector_angle.hpp"

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
	void setPathEnd(std::pair<glm::vec3, glm::vec3> p)
	{
		outerPathEnd = p;
	}
	void setInnerPathEnd(glm::vec3 p)
	{
		innerPathEnd = p;
	}

	void setPaused(bool p);
	bool getPaused();

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

	std::pair<glm::vec3, glm::vec3> getOuterPathEnd()
	{
			return outerPathEnd;
	}

	glm::vec3 getInnerPathEnd()
	{
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

	bool getJump()
	{
		return Jump;
	}

	void setAnimValues(float s, float e)
	{
		animStart = s;
		animEnd = e;
		setAnimation(s, e);
	}

private:
	
	std::vector<glm::vec3> outerPath;
	std::vector<glm::vec3> innerPath;
	std::pair<glm::vec3, glm::vec3> outerPathEnd;
	glm::vec3 innerPathEnd;

	bool inside;
	bool outsideMovement;
	int jumpingCounter;
	bool Jump;
	bool moving;
	
	bool paused;

	float velocity;
	float angularVelocity;

	Player* target;
	glm::vec3 currentTargetPosition;

	float animStart = 0.0f;
	float animEnd = 0.0f;
};

