#define GLM_ENABLE_EXPERIMENTAL
#pragma once
#include "GameObject.h"
#include "Shader.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include "glm/gtx/vector_angle.hpp"

class Boss: public GameObject
{
public:
	struct Character {
		std::string name;
		std::string fileLocation;
		bool isLocked;
	};

	Boss(Character character);
	~Boss();


	//just give him 4 predefined paths to choose from, he then stops and does ambient animations

	//function to give its pathfinding movement
	void setPath(std::vector<glm::vec3> p, bool outer);
	void setPathEnd(glm::vec3 p)
	{
		outerPathEnd.push_back(p);
	}

	void setPaused(bool p);
	bool getPaused();


	glm::vec3 getOuterPathEnd(int position)
	{
		return outerPathEnd.at(position);
	}


	std::vector<glm::vec3> getPath();

	void update() override;

	glm::vec3 rotation;

	glm::vec3 getSpawnPoint()
	{
		return selectedSpawnPoint;
	}

	
private:

	std::vector<std::vector<glm::vec3>> outerPath;
	std::vector<glm::vec3> outerPathEnd;
	std::vector<glm::vec3> spawnPoints;

	std::vector<glm::vec3> selectedPath;
	glm::vec3 selectedPathEnd;
	glm::vec3 selectedSpawnPoint;

	bool outsideMovement;

	bool paused;

	float velocity;
	float angularVelocity;

};

