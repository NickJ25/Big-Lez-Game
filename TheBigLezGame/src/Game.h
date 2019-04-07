#pragma once
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <vector>
#include <iostream>

// Include Audio engine
#include <irrKlang.h>

//test include
#include "Shader.h"
#include "Model.h"
#include "Prop.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "Camera.h"
#include "Skybox.h"
#include "Player.h"
#include "Button.h"
#include "Image.h"
#include "WaveSpawner.h"
#include "Boss.h"
#include "Text.h"
#include "Grid.h"
#include "PathManager.h"
#include "ControllerComponent.h"
#include "Obstacle.h"

using namespace std;

class Game {
private:
	Player* ALL_PLAYERS[2]; // Hold all players in this array?

	Player* mainPlayer;
	Text* testtxt;
	bool isGameRunning = true; 
	Button* resumeBtn, *mainMenuBtn;
	GLFWwindow* g_window;
	Menu* selectedMenu;
	Image* pauseBackground;
	Text* testtxt2;
	bool showBoundingBoxes;
	int penetrationDepthX;
	int penetrationDepthZ;
	bool clicked = false;

	//storage for the spawned waves
	vector<vector<GameObject*>> mapWaves;

	vector<GameObject*> firstWave;
	vector<GameObject*> secondWave;
	vector<GameObject*> thirdWave;
	vector<GameObject*> fourthWave;
	vector<GameObject*> fifthWave;
	vector<GameObject*> sixthWave;

	vector<int> waveCounters;

	int currentWave;

	int firstWaveCounter;

	//record if there are enemies on the map
	bool mapEmpty = false;
	int enemyCounter = 0;

	//utility functions for testing
	bool takeDamage = false;

	//float wavetimer
	float waveTimer = 15.0f; // 6 seconds between the end of one wave and the start of the next, 15 to allow time for loading

	//time between ticks
	float deltaTime = 0.0f;

	//for calcualting delta time
	float currentTime = 0.0f;
	float previousTime = 0.0f;

	//check if the game has been completed
	bool gameWon = false;

	Text* waveText;
	float textAlpha = 1.0f;
	float transparency = 1.0f;

	//sync up sounds waves and animations
	bool initialised = false;

	//background music engine
	irrklang::ISoundEngine *AmbientEngine = irrklang::createIrrKlangDevice();
	bool ambientInitialised = false;

	//wave spawner noise engine
	irrklang::ISoundEngine *WaveEngine = irrklang::createIrrKlangDevice();
	bool waveInitialised = false;

	//conversation noise engine
	irrklang::ISoundEngine *conversationEngine = irrklang::createIrrKlangDevice();

	//sound numbers
	int noOfSounds = 0;

	//sound timers
	float conversationTimer = 15.0f;

	//conversations
	vector<vector<float>> convos;
	vector<vector<string>> convoOrders;
	bool convoAssigned = false;

	Image* bossHealth;
	bool ableTo = true;

public:
	Game() 
	{
		init();
		initialised = true;
	};
	~Game() {};
	void init();
	void update();
	void draw();
	bool checkCollision(GameObject* a, GameObject* b);
	bool checkRayToAABB(glm::vec3* rayPos, glm::vec3* rayDir, GameObject * object);

	//adding characters details
	void addCharacterSounds(string charName);
	vector<irrklang::ISoundSource*> loadSounds(string character);

	//for calculating contact normal
	const glm::vec3 nup = glm::vec3(0, 1, 0);
	const glm::vec3 ndown = glm::vec3(0, -1, 0);
	const glm::vec3 nright = glm::vec3(1, 0, 0);
	const glm::vec3 nleft = glm::vec3(-1, 0, 0);

	char computePointMask(glm::vec3 p, Enemy* e);
	glm::vec3 getFaceNormal(glm::vec3 p, Enemy* e);
	bool pointIsAbovePlane(const glm::vec3 & P, const glm::vec3 & n, float d);

	void generateWave(int waveNumber);

	glm::vec3 contactNormal;
};
