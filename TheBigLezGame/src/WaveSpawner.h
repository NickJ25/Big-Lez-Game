#pragma once
#include <glm/common.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Player.h"

class WaveSpawner : public GameObject
{
public:
	//object is a big circle
	WaveSpawner();


	//function to get random co-ordinates
	glm::vec2 getSpawnCoord();
	
	//array of predefined numbers to correspond to enemies in each wave
	void spawnWave(std::vector<GameObject*> &gameObjects, int wavenumber, Shader* shader);
	

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

	//enemies
	Player::Character normalChoomah;
	Player::Character chargerChoomah;
	Player::Character brawlerChoomah;
	Player::Character bossChoomah;
};