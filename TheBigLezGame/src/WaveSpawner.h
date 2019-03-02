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

class WaveSpawner : public GameObject
{
public:
	WaveSpawner(Grid* g);

	//function to get random co-ordinates from the preset coordinates
	glm::vec2 getSpawnCoord();

	void setEndCoords(std::vector<glm::vec3> e);
	glm::vec3 getEndCoord();
	
	//array of predefined numbers to correspond to enemies in each wave
	void spawnWave(std::vector<GameObject*> &gameObjects, int wavenumber, Shader* shader, PathManager* pathManager);
	
	//set up the enemy gameobjects for spawning
	void initNPCs();

	void update() override {}

private:

	//position values
	float radius;
	glm::vec3 position;

	//wave container
	std::vector<vector<int>> waves;

	//spawn points
	std::vector<glm::vec2> spawnPoints;
	std::vector<glm::vec3> endPoints;

	//enemies
	Enemy::Character normalChoomah;
	Enemy::Character chargerChoomah;
	Enemy::Character brawlerChoomah;
	Enemy::Character bossChoomah;

	//the worlds grid
	Grid* grid;
};