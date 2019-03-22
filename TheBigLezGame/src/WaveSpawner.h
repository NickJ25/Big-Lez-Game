#pragma once
#include <glm/common.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Player.h"
#include "PathManager.h"
#include "Grid.h"
//#include "Boss.h"
class Boss;
class WaveSpawner : public GameObject
{
public:
	WaveSpawner();

	//function to get random co-ordinates from the preset coordinates
	glm::vec2 getSpawnCoord(int type);

	void setEndCoords(std::vector<std::pair<glm::vec3,glm::vec3>> e, int type);

	std::pair<glm::vec3, glm::vec3> getEndCoord(int type);
	
	//array of predefined numbers to correspond to enemies in each wave
	void spawnWave(std::vector<GameObject*> &gameObjects, int wavenumber, Shader* shader, PathManager* pathManager);
	
	//set up the enemy gameobjects for spawning
	void initNPCs();

	void update() override {}

	int getType();

	void setWave(std::vector<int> w)
	{
		waves.push_back(w);
	}

	std::vector<vector<int>> getWaves()
	{
		return waves;
	}

	void spawnEnemy(std::vector<GameObject*>& currentObj, std::vector<GameObject*> &gameObjects)
	{
		if(toBeSpawned.size() == 0)
			toBeSpawned = currentObj;
		if (!toBeSpawned.empty()) {
			GameObject* tmp = toBeSpawned.at(0);
			toBeSpawned.erase(toBeSpawned.begin());
			gameObjects.push_back(tmp);
			//delete tmp;
		}
	}
private:

	//position values
	float radius;
	glm::vec3 position;

	//wave container
	std::vector<vector<int>> waves;

	//points of interest
	std::vector<glm::vec2> spawnPointsBottom;
	std::vector<glm::vec2> spawnPointsTop;
	std::vector<glm::vec2> spawnPointsLeft;
	std::vector<glm::vec2> spawnPointsRight;

	std::vector<std::pair<glm::vec3, glm::vec3>> endPointsBottom;
	std::vector<std::pair<glm::vec3, glm::vec3>> endPointsTop;
	std::vector<std::pair<glm::vec3, glm::vec3>> endPointsLeft;
	std::vector<std::pair<glm::vec3, glm::vec3>> endPointsRight;

	//types
	int types[3] = {0, 1, 2};
	int currentType = 0;
	int lastType = 1;

	//enemies
	Enemy::Character normalChoomah;
	Enemy::Character chargerChoomah;
	Enemy::Character brawlerChoomah;

	//optimisation controller
	std::vector<GameObject*> toBeSpawned;
};