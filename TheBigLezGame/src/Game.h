#pragma once
#include <GL/glew.h>
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
#include "GameData.h"

using namespace std;

class Game {
private:
	vector<Player*> playerList{nullptr, nullptr};
	glm::vec3 startingPositions[2] = { glm::vec3(75.0f, -2.4f, 15.0f), glm::vec3(45.0f, -2.4f, 15.0f) };
	void createPlayers();
	void assignAttributes(int n);
	void createWeapons();

	bool isGameRunning = true; 
	Button* resumeBtn, *mainMenuBtn, *quitBtn, *exitBtn;
	GLFWwindow* g_window;
	Menu* selectedMenu;
	Image* pauseBackground;
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

	//record if there are players/enemies on the map
	bool mapEmpty = false;
	int enemyCounter = 0;
	int playerCounter = 0;

	//utility functions for testing
	bool takeDamage = false;

	//float wavetimer
	float waveTimer = 30.0f; // 6 seconds between the end of one wave and the start of the next, 15 to allow time for loading

	//time between ticks
	float deltaTime = 0.0f;

	//for calcualting delta time
	float currentTime = 0.0f;
	float previousTime = 0.0f;

	//check if the game has been completed
	bool gameWon = false;
	bool gameLost = false;

	//HUD text
	Text* waveText;
	Text* bossText;
	Text* endGameText;
	float textAlpha = 1.0f;
	float transparency = 1.0f;

	//sync up sounds waves and animations
	bool initialised = false;

	//background music engine
	irrklang::ISoundEngine *AmbientEngine = irrklang::createIrrKlangDevice();
	bool ambientInitialised = false;
	bool waveInitialised = false;

	//sound numbers
	int noOfSounds = 0;

	//sound timers
	float conversationTimer = 30.0f;

	//conversations
	vector<vector<float>> convos;
	vector<vector<string>> convoOrders;
	bool convoAssigned = false;

	//splitscreen modelview buffer
	GLuint uniform_buffer;

	Image* bossHealth;
	bool ableTo = true;

	GameObject* bar;
	Text* barInfo;

	//collision tools
	Enemy *e1;
	Enemy *e2;
	Player *p1;
	Player *p2;
	Obstacle *ob1;
	Obstacle *ob2;
	Prop *pr1;
	Prop *pr2;

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

	//collision detection
	bool checkCollision(GameObject* a, GameObject* b);
	bool checkRayToAABB(glm::vec3* rayPos, glm::vec3* rayDir, GameObject * object);

	//collision resolution
	void playerEnemyCollision(GameObject* a, GameObject* b);
	void barInteraction(Player* p);

	//update functions
	void conversationUpdate();

	//adding characters details
	void addCharacterSounds(string charName);
	vector<irrklang::ISoundSource*> loadSounds(string character);

	void generateWave(int waveNumber);
};
