#define GLM_ENABLE_EXPERIMENTAL
#pragma once
#include "GameObject.h"
#include "Shader.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include "glm/gtx/vector_angle.hpp"
#include "PathManager.h"
class WaveSpawner;
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
	void setPathEnd(glm::vec3 p);

	void setPaused(bool p);
	bool getPaused();


	glm::vec3 getOuterPathEnd(int position);


	std::vector<glm::vec3> getPath();

	void update() override;

	glm::vec3 rotation;

	glm::vec3 getSpawnPoint();

	void checkFieldEmpty(std::vector<GameObject*> g);

	void initialiseWaveSpawner();

	void spawnMinions(std::vector<GameObject*> &g, Shader* shader, PathManager* pathmanager);

	int getCurrentWave();

private:

	WaveSpawner *privateSpawner;
	std::vector<std::vector<glm::vec3>> outerPath;
	std::vector<glm::vec3> outerPathEnd;
	std::vector<glm::vec3> spawnPoints;

	std::vector<glm::vec3> selectedPath;
	glm::vec3 selectedPathEnd;
	glm::vec3 selectedSpawnPoint;

	bool outsideMovement;
	bool canSpawn = true;
	bool paused;
	bool stopped = false;

	float velocity;
	float angularVelocity;

	std::vector<std::vector<int>> bossWaves;
	std::vector<int> normalWave;
	std::vector<int> chargerWave;
	std::vector<int> brawlerWave;

	std::vector<GameObject*> normalObj;
	//std::vector<
	std::vector<int> current;

	int spawnCounter = 0;
	int currentWave = 0;
	int numToBeSpawned = 0;
	bool waveSet = false;
	bool waveSpawned = false;

};

