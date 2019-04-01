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

class PathManager;
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

	//set the end point to the outer path, and also the start point of the inner path
	void setPathEnd(std::pair<glm::vec3, glm::vec3> p);

	//retrive these values
	std::pair<glm::vec3, glm::vec3> getOuterPathEnd();

	//find the targets current position
	void setInnerPathEnd(glm::vec3 p);

	//pause functionality to stop animations and movement when paused
	void setPaused(bool p);
	bool getPaused();

	//set the assigned player as target
	void setTarget(Player* p);

	//retrieve this target
	Player* getTarget();

	//check current recorded player location
	glm::vec3 getInnerPathEnd();

	//check if this enemy is inside the house
	bool getLocation();

	//set the boolean value dictating whether the enemy is moving or not
	void setMoving(bool newMove);

	//retrieve the enemies path to the house
	std::vector<glm::vec3> getPath();

	//overloaded from superclass
	void update() override;

	//public rotation
	glm::vec3 rotation;

	//retrieve targets position
	glm::vec3 getCurrentTargetPosition();

	//set targets position 
	void setCurrentTargetPosition(glm::vec3 p);

	//check if the enemy is currently jumping
	bool getJump();

	//set animation start and end values
	void setAnimValues(float s, float e);

	//reset all the enemies animation speed and position variables
	void reset(PathManager* pathmanager);

	//record the enemies spawn point
	void setSpawnPoint(glm::vec3 p);

	string getName();

	//injury
	void takeDamage(float damage);

	//death
	void death();

	float getHealth();

	bool getInjured();

private:
	
	float health;
	float originalHealth;

	int injuryAnimationTimer = 40;
	bool injured = false;

	int deathAnimationTimer = 150;
	bool dead = false;

	//rotation variables
	bool rotated = false;
	bool nodeSet = false;
	glm::vec3 currentNode;

	//spawning and pathing variables
	glm::vec3 spawnPoint;
	std::vector<glm::vec3> outerPath;
	std::vector<glm::vec3> innerPath;
	std::pair<glm::vec3, glm::vec3> outerPathEnd;
	glm::vec3 innerPathEnd;

	//store each enemies animation
	std::vector<std::vector<pair<float, float>>> injuryAnimations;
	std::vector<std::vector<pair<float, float>>> deathAnimations;

	//movement regulating variables
	bool inside;
	bool outsideMovement;
	int jumpingCounter;
	bool Jump;
	bool moving;
	
	//pausing variable
	bool paused;

	//physics variables
	float velocity;
	float angularVelocity;

	//target variables
	Player* target;
	glm::vec3 currentTargetPosition;

	//animation variables
	float animStart = 0.0f;
	float animEnd = 0.0f;

	//reset variables
	float originalVelocity;
	std::vector<glm::vec3> originalOuterPath;
	glm::vec3 originalPosition;
	bool firstPosition;

	//characters name
	string name;
};

