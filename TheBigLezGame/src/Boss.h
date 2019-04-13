#define GLM_ENABLE_EXPERIMENTAL
#pragma once
//files needed for boss
#include "GameObject.h"
#include "Shader.h"
#include "Player.h"
#include "Enemy.h"
#include "PathManager.h"

//std library
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

//Audio engine
#include <irrKlang.h>

//GLM
#include "glm/gtx/vector_angle.hpp"

//forward declaration for wavespawner
class WaveSpawner;
class Boss: public GameObject
{
public:
	//character struct to hold certain information
	struct Character {
		std::string name;
		std::string fileLocation;
		bool isLocked;
	};

	//constructor/destructor
	Boss(Character character);
	~Boss();

	//function to give its path end
	void setPathEnd(glm::vec3 p);

	//pause functionality
	void setPaused(bool p);
	bool getPaused();


	//inherited from GameObject
	void update() override;

	//returns a spawn point
	glm::vec3 getSpawnPoint();

	//check if there are other enemies on the field
	void checkFieldEmpty(std::vector<GameObject*> g);

	//sets up the wave information
	void initialiseWaveSpawner(vector<GameObject*> gameObjects, Shader* shader, PathManager* pathmanager);

	//spawns a wave, one minion at a time
	void spawnMinions(std::vector<GameObject*> &g, Shader* shader, PathManager* pathmanager);

	//current wave controls
	int getCurrentWave();
	void setWave();

	//for injury
	void takeDamage(float damage);

	//called when dead
	void death();

	//returns health clipped between 0 and 1 for scaling purposes
	float getHealth();

	void setHealth(float num);

private:

	//timing variables
	float currentTime = 0.0f;
	float previousTime = 0.0f;

	//health variables
	float health = 2400.0f;
	float armour = 45.0f;

	//death variables
	bool dead = false;
	bool deadSet = false;
	float deathStart = 0.0f;
	float deathAnimationTimer = 1.67f;

	//sound stuff
	irrklang::ISoundEngine *privateEngine = irrklang::createIrrKlangDevice();
	bool soundSet = false;

	irrklang::ISoundEngine *speechEngine = irrklang::createIrrKlangDevice();
	vector<irrklang::ISoundSource*> sounds;
	float speechTimer = 5.0f;

	//wave spawning functionality
	WaveSpawner *privateSpawner;
	std::vector<std::vector<glm::vec3>> outerPath;
	std::vector<glm::vec3> outerPathEnd;
	std::vector<glm::vec3> spawnPoints;

	std::vector<glm::vec3> selectedPath;
	glm::vec3 selectedPathEnd;
	glm::vec3 selectedSpawnPoint;

	//movement control variables
	bool outsideMovement;
	bool canSpawn = true;
	bool paused;
	bool stopped = false;

	//physics variables
	float velocity;
	float angularVelocity;

	glm::vec3 rotation;

	//wave storage
	std::vector<std::vector<int>> bossWaves;
	std::vector<int> normalWave;
	std::vector<int> chargerWave;
	std::vector<int> brawlerWave;

	std::vector<GameObject*> normalObj;
	std::vector<GameObject*> chargerObj;
	std::vector<GameObject*> brawlerObj;

	//current wave and object storage
	std::vector<int> current;
	std::vector<GameObject*> currentObj;


	int spawnCounter = 3;
	int currentWave = 0;
	int numToBeSpawned = 0;

	//wave control variables
	bool waveSet = false;
	bool waveSpawned = false;

	//animation varaibles
	int animationTimer = 144;
	bool animating = false;
	string animType = " ";

};

