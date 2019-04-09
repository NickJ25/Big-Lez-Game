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
#include <irrKlang.h>

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

	void initialiseWaveSpawner(vector<GameObject*> gameObjects, Shader* shader, PathManager* pathmanager);

	void spawnMinions(std::vector<GameObject*> &g, Shader* shader, PathManager* pathmanager);

	int getCurrentWave();

	void setWave();

	void takeDamage(float damage);

	void death();

	//returns health clipped between 0 and 1 for scaling purposes
	float getHealth();

	void setHealth(float num)
	{
		health += num;
	}
private:

	//timing variables
	float currentTime = 0.0f;
	float previousTime = 0.0f;

	float health = 2400.0f;
	float armour = 45.0f;

	bool dead = false;
	bool deadSet = false;
	float deathStart = 0.0f;

	irrklang::ISoundEngine *privateEngine = irrklang::createIrrKlangDevice();
	bool soundSet = false;

	irrklang::ISoundEngine *speechEngine = irrklang::createIrrKlangDevice();
	vector<irrklang::ISoundSource*> sounds;
	float speechTimer = 5.0f;


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
	std::vector<GameObject*> chargerObj;
	std::vector<GameObject*> brawlerObj;

	std::vector<int> current;
	std::vector<GameObject*> currentObj;

	int spawnCounter = 3;
	int currentWave = 0;
	int numToBeSpawned = 0;
	bool waveSet = false;
	bool waveSpawned = false;

	//equivalent of 6 seconds
	int animationTimer = 144;
	bool animating = false;
	string animType = " ";

};

