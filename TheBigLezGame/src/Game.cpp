#include "Game.h"
#include <Windows.h>
#include "Gun.h"

vector<GameObject*> gameObjects;
vector<GameObject*> collisionObjs;
Skybox* skybox;
Shader *toonShader;
WaveSpawner* waveSpawner;
Grid* pathFindingGrid;
PathManager* pathManager;
Prop* collisionTest;

GameObject* sassy;

struct materialStruct
{
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat shininess;
};

materialStruct material0 = {
	{0.0f, 0.8f, 0.2f, 1.0f}, // ambient
	{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
	{0.0f, 0.1f, 0.0f, 1.0f}, // specular
	2.0f  // shininess
};

int diffuse = 0;
int specular = 1;
float shininess = 32.0f;

void Game::assignAttributes(int n)
{
	if (GameData::g_PlayerData[n]->name == "Leslie")
	{
		playerList[n]->setCharacterAttributes(300, 2.5);
		//set run
		playerList[n]->setAnimationCalls(0.0, 7.625, 0);
		////set still
		playerList[n]->setAnimationCalls(5.208, 2.103, 1);
		////set death
		playerList[n]->setAnimationCalls(5.0, 2.541, 2);
		////set deathstill
		playerList[n]->setAnimationCalls(6.041, 0.0, 3);
	}

	if (GameData::g_PlayerData[n]->name == "Sassy")
	{
		playerList[n]->setCharacterAttributes(450, 2.5);
		//set run
		playerList[n]->setAnimationCalls(0.0, 2.7, 0);
		////set still
		playerList[n]->setAnimationCalls(2.083, 2.7, 2);

		//currently dont have animations for it
		////set death
		playerList[n]->setAnimationCalls(0.0, 1.0, 1);
		////set deathstill
		playerList[n]->setAnimationCalls(0.0, 1.0, 3);
	}

	if (GameData::g_PlayerData[n]->name == "Donny")
	{
		playerList[n]->setCharacterAttributes(300, 1.5);
		//set run
		playerList[n]->setAnimationCalls(0.0, 6.045, 0);
		////set still
		playerList[n]->setAnimationCalls(0.916, 6.045, 2);
		////set death
		playerList[n]->setAnimationCalls(0.916, 3.594, 1);
		////set deathstill
		playerList[n]->setAnimationCalls(1.541, 3.594, 3);
	}
}
void Game::createPlayers()
{
	for (int i = 0; i < GameData::g_PlayerData.size(); i++) {
		if (GameData::g_PlayerData[i] != nullptr) {
			playerList[i] = new Player(GameData::g_PlayerData[i]->control, *GameData::g_PlayerData[i], startingPositions[i]);
			assignAttributes(i);
			playerList[i]->setShader(toonShader);
			playerList[i]->addCollision(glm::vec3(45.0f, -12.5f, 20.0f), 5.0f, 5.0f);
			playerList[i]->setPlayerNum(i);
			gameObjects.push_back(playerList[i]);
		}
	}

	int lCounter = 0, sCounter = 0, dCounter = 0, cCounter = 0;

	//find out whose in the game
	for (int j = 0; j < GameData::g_PlayerData.size(); j++)
	{
		if (playerList[j] == nullptr)
			break;
		if (playerList[j]->getCharacter().name == "Leslie")
			lCounter++;
		else
		if (playerList[j]->getCharacter().name == "Sassy")
			sCounter++;
		else
		if (playerList[j]->getCharacter().name == "Donny")
			dCounter++;
		else
		if (playerList[j]->getCharacter().name == "Clarence")
			cCounter++;
	}

	//finds out which character is missing and puts them behind the bar 
	GameObject* extraChar;
	if (lCounter == 0)
	{
		extraChar = new Prop("assets/Characters/BigLez/lez3.dae", glm::vec3(0.0f, 0.0f, 0.0f));
	}else
		if (sCounter == 0)
		{
			extraChar = new Prop("assets/Characters/Sassy/sassy.dae", glm::vec3(0.0f, 0.0f, 0.0f));
		}else
			{
			extraChar = new Prop("assets/Characters/Donny/donny.dae", glm::vec3(0.0f, 0.0f, 0.0f));
			}

		extraChar->setPaused(true);
		extraChar->setShader(toonShader);
		extraChar->setPosition(glm::vec3(60.0f, -12.5f, -7.5f));
		gameObjects.push_back(extraChar);

}

void Game::createWeapons()
{
	for (int i = 0; i < playerList.size(); i++) {
		if (playerList[i] != nullptr) {
			switch (playerList[i]->getCharacter().id) {
			case 1: // Gun Setup for BigLez
			{
				// Lez's Shotgun
				GameObject* lezShotgun = new Gun("assets/Weapons/LezShotgun/lezshotgun.dae", "Shotgun", 8, 8, 1.0, false);
				lezShotgun->setShader(toonShader);
				lezShotgun->setAnimation(0.0f, 3.0f);
				playerList[i]->addWeapon(dynamic_cast<Weapon*> (lezShotgun));
				gameObjects.push_back(lezShotgun);

				break;
			}
			case 2: // Gun Setup for Sassy
			{
				GameObject* donnyRifle = new Gun("assets/Weapons/DonnyRifle/DonnyRifle.dae", "Rifle", 6, 6, 2, false);
				donnyRifle->setShader(toonShader);
				donnyRifle->setAnimation(4.0f, 1.0f);
				playerList[i]->addWeapon(dynamic_cast<Weapon*> (donnyRifle));
				gameObjects.push_back(donnyRifle);
				break;
			}
			case 3: // Gun Setup for Donny
			{
				GameObject* donnyPistol = new Gun("assets/Weapons/DonnyPistol/DonnyPistol.dae", "Pistol", 8, 8, 0.2, false);
				donnyPistol->setShader(toonShader);
				donnyPistol->setAnimation(0.0f, 1.0f);
				playerList[i]->addWeapon(dynamic_cast<Weapon*> (donnyPistol));
				gameObjects.push_back(donnyPistol);
				break;
			}
			case 4: // Gun Setup for Clarence
			{
				cout << "------------------------------------c guns" << "\n";
				break;
			}
			default:
				cout << "couldn't find player" << "\n";
			}
		}
	}
}

#pragma region Initialise
void Game::init()
{
#pragma region Utility and shaders

	std::cout << "Game.cpp Init" << std::endl;

	//initialise shaders from file sources
	toonShader = new Shader("src/toonShader.vert", "src/toonShader.geom", "src/toonShader.frag");

	skybox = new Skybox("assets/Skybox/back.bmp", "assets/Skybox/front.bmp",
						"assets/Skybox/right.bmp", "assets/Skybox/left.bmp",
						"assets/Skybox/top.bmp", "assets/Skybox/bottom.bmp");

	//for bounding box debug tool
	showBoundingBoxes = false;

	// Uniform buffer for splitscreen modelview data
	glGenBuffers(1, &uniform_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer);
	glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);

#pragma endregion
#pragma region Object initialisation

	////	Init Objects	////
	GameObject* dirLight = new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.9f, 0.9f, 0.9f));
	dirLight->setShader(toonShader);
	gameObjects.push_back(dirLight);

	GameObject* environment = new Prop("assets/Props/Map/envMap1.dae", glm::vec3(0.0f, 20.0f, 100.0f));
	environment->setShader(toonShader);
	environment->Move(glm::vec3(0.0f, 60.0f, 0.0f));
	gameObjects.push_back(environment);

	GameObject* roof = new Prop("assets/Props/Map/roof.dae", glm::vec3(0.0f, 0.0f, 0.0f));
	roof->setShader(toonShader);
	roof->Scale(glm::vec3(1.5f, 1.5f, 1.5f));
	roof->Move(glm::vec3(17.5f, -70.0f, 65.5f));
	gameObjects.push_back(roof);


	const char* file = "assets/Props/Map/gridblock.dae";
	bar = new Prop(file, glm::vec3(0.0f, 0.0f, 0.0f));
	bar->setShader(toonShader);
	bar->addCollision(glm::vec3(60.0f, 0.0f, 0.0f), 5.0f, 2.0f);
	gameObjects.push_back(bar);

	createPlayers();
	createWeapons();

#pragma endregion
#pragma region Fences & Wave Junk
	// add environmental collision boxes for pathfinding an' such
	glm::vec3 fenceScaleVertical = glm::vec3(1.0f, 4.0f, 35.0f);
	glm::vec3 fenceScaleHorizontal = glm::vec3(35.0f, 4.0f, 1.0f);
	glm::vec3 test = glm::vec3(2.5, 2.5, 2.5);
	GameObject* Fence;

	for (int i = 0; i < 14; i++)
	{
		Fence = new Obstacle("collider", glm::vec3(0.0, 0.0, 0.0));


		//for the left and right fences
		glm::vec3 scaleFactor = fenceScaleVertical;
		if (i >= 4 && i < 7) scaleFactor = fenceScaleHorizontal;
		if (i == 8 || i == 12) scaleFactor = glm::vec3(17.5f, 4.0, 2.0f);
		if (i == 9 || i == 11) scaleFactor = glm::vec3(10.5f, 4.0, 3.0f);
		if (i == 10) scaleFactor = glm::vec3(2.0f, 4.0, 3.0f);
		if (i == 13) scaleFactor = glm::vec3(2.0f, 0.0f, 27.5f);


		//apply the selected scale first
		Fence->Scale(scaleFactor);

		glm::vec3 pos;

		//fences
		//left fences
		if (i == 0) { pos = glm::vec3(-50.0f, 0.0f, 35.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
		if (i == 1) { pos = glm::vec3(-50.0f, 0.0f, -75.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

		//right fences
		if (i == 2) { pos = glm::vec3(145.0f, 0.0f, 35.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
		if (i == 3) { pos = glm::vec3(145.0f, 0.0f, -75.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

		//top fences left to right
		if (i == 4) { pos = glm::vec3(-125.0f, 0.0f, -165.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
		if (i == 5) { pos = glm::vec3(-10.0f, 0.0f, -165.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
		if (i == 6) { pos = glm::vec3(98.0f, 0.0f, -165.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
		if (i == 7) { pos = glm::vec3(204.0f, 0.0f, -165.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

		////house in the middle 
		//front of house
		if (i == 8) { pos = glm::vec3(17.5f, 0.0f, -15.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
		if (i == 9) { pos = glm::vec3(62.5f, 0.0f, -10.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

		//right hand side of the house
		if (i == 10) { pos = glm::vec3(90.0f, 0.0f, 15.75f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

		//rear of the house
		if (i == 11) { pos = glm::vec3(62.5f, 0.0f, 44.0f); Fence->addCollision(pos, scaleFactor.x, 2.0f); }
		if (i == 12) { pos = glm::vec3(17.5f, 0.0f, 44.0f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

		//left of house 45 to -10 at 0 
		if (i == 13) { pos = glm::vec3(0.0f, 0.0f, 17.5f); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
		//add collision objects to the game objects vector
		gameObjects.push_back(Fence);

	}

	//first initialise a Fector containing door information
	std::vector<std::pair<glm::vec3, glm::vec3>> bottomDoors, topDoors, leftDoors, rightDoors;

	bottomDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(83.0f, -12.5f, 60.0f), glm::vec3(83.0f, -12.5f, 50.0f)));
	//bottomDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(43.0f, -12.5f, 50.0f), glm::vec3(43.0f, -12.5f, 30.0f)));

	//topDoors.push_back(std::pair<glm::vec3, glm::vec3> (glm::vec3(83.0f, -12.5f, -30.0f), glm::vec3(83.0f,-12.5f,-10.0f)));
	topDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(43.0f, -12.5f, -30.0f), glm::vec3(43.0f, -12.5f, -10.0f)));

	rightDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(100.0f, -12.5f, -6.0f), glm::vec3(80.0f, -12.5f, -6.0f)));
	rightDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(100.0f, -12.5f, 35.0f), glm::vec3(80.0f, -12.5f, 35.0f)));


	//grid has to be the last game object added
	pathFindingGrid = new Grid(glm::vec2(500, 500), 5.0f, glm::vec3(0.0f, 0.0f, 0.0f), "boundingbox");
	pathFindingGrid->buildGrid(gameObjects, toonShader);

	//initialise the path manager
	pathManager = new PathManager();
	pathManager->addGrid(pathFindingGrid);

	//set up the wavespawner
	waveSpawner = new WaveSpawner();

	// numbers correspond to number of each choomah type per round
	vector<int> wave1, wave2, wave3, wave4, wave5, wave6, wave7;
	wave1.push_back(0), wave1.push_back(2), wave1.push_back(0), wave1.push_back(0); 
	wave2.push_back(0), wave2.push_back(2), wave2.push_back(1), wave2.push_back(0); 
	wave3.push_back(0), wave3.push_back(2), wave3.push_back(2), wave3.push_back(0); 
	wave4.push_back(0), wave4.push_back(3), wave4.push_back(2), wave4.push_back(0); 
	wave5.push_back(0), wave5.push_back(3), wave5.push_back(3), wave5.push_back(0); 
	wave6.push_back(0), wave6.push_back(0), wave6.push_back(0), wave6.push_back(1);
	//wave7.push_back(1), wave7.push_back(0), wave7.push_back(0), wave7.push_back(0);

	//add this wave to the wave spawner
	waveSpawner->setWave(wave1);
	waveSpawner->setWave(wave2);
	waveSpawner->setWave(wave3);
	waveSpawner->setWave(wave4);
	waveSpawner->setWave(wave5);
	waveSpawner->setWave(wave6);
	//waveSpawner->setWave(wave7);

	firstWaveCounter = 15;

	waveSpawner->setEndCoords(bottomDoors, 0);
	waveSpawner->setEndCoords(topDoors, 1);
	waveSpawner->setEndCoords(rightDoors, 2);
	//dlc
	//waveSpawner->setEndCoords(leftDoors, "Left");

	int waveCount = 0;

	while(firstWave.size() < 2) { 
		waveSpawner->spawnWave(gameObjects, 0, toonShader, pathManager, true, firstWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;
	while (secondWave.size() < 3)
	{
		waveSpawner->spawnWave(gameObjects, 1, toonShader, pathManager, true, secondWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;
	while (thirdWave.size() < 4)
	{
		waveSpawner->spawnWave(gameObjects, 2, toonShader, pathManager, true, thirdWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;
	while (fourthWave.size() < 5)
	{
		waveSpawner->spawnWave(gameObjects, 3, toonShader, pathManager, true, fourthWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;
	while (fifthWave.size() < 6)
	{
		waveSpawner->spawnWave(gameObjects, 4, toonShader, pathManager, true, fifthWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;
	while (sixthWave.size() < 1) 
	{
		waveSpawner->spawnWave(gameObjects, 5, toonShader, pathManager, true, sixthWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;



	//add the waves to the wave generating vector
	mapWaves.push_back(firstWave);
	mapWaves.push_back(secondWave);
	mapWaves.push_back(thirdWave);
	mapWaves.push_back(fourthWave);
	mapWaves.push_back(fifthWave);
	mapWaves.push_back(sixthWave);

	vector<string> playerNames;
	//set up audio depending on what characters are present
	for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end(); ++it)
	{
		Player *p = dynamic_cast<Player*>(*it);

		//add player names to temporary vector
		if (p)
			playerNames.push_back(p->getCharacter().name);
	}

	int LezCounter = 0;
	int SassyCounter = 0;
	int DonnyCounter = 0;
	int ClarenceCounter = 0;

	//find missing character of the possible 4 ( 2 missing if playing single player ) 
	for (int i = 0; i < playerNames.size(); i++)
	{
		if (playerNames[i] == "Clarence")
		{
			ClarenceCounter++;
		}
		if (playerNames[i] == "Donny")
		{
			DonnyCounter++;
		}
		if (playerNames[i] == "Sassy")
		{
			SassyCounter++;
		}
		if (playerNames[i] == "Lez")
		{
			LezCounter++;
		}
	}

	if (ClarenceCounter == 0)
	{
	
		//firstly add all their relevant one liners
		vector<float> times; // in seconds
		vector<string> orders;

		//add lez lines
		addCharacterSounds("Lez");

		times.push_back(0.0f);
		orders.push_back("Lez");

		//add the same orders and times 3 times, once for each line
		for (int i = 0; i < 3; i++) {
			convos.push_back(times);
			convoOrders.push_back(orders);
			noOfSounds++;
		}

		times.clear();
		orders.clear();

		//add sassy lines
		addCharacterSounds("Sassy");

		times.push_back(0.0f);
		orders.push_back("Sassy");

		//add the same orders and times 3 times, once for each line
		for (int i = 0; i < 3; i++) {
			convos.push_back(times);
			convoOrders.push_back(orders);
			noOfSounds++;
		}

		times.clear();
		orders.clear();

		//add donny lines
		addCharacterSounds("Donny");

		times.push_back(0.0f);
		orders.push_back("Donny");

		//add the same orders and times 3 times, once for each line
		for (int i = 0; i < 3; i++) {
			convos.push_back(times);
			convoOrders.push_back(orders);
			noOfSounds++;
		}

		times.clear();
		orders.clear();
		//push back donny, lez and sassy conversations

		//3 of each 

		//lez sassy conversation
		irrklang::ISoundSource* LSconvo1 = AmbientEngine->addSoundSourceFromFile("assets/Sounds/Lez/LezSassy1.wav"); //conversation
		irrklang::ISoundSource* LSconvo2 = AmbientEngine->addSoundSourceFromFile("assets/Sounds/Sassy/LezSassy1.wav"); //conversation
		for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end(); ++it)
		{
			Player *p = dynamic_cast<Player*>(*it);

			//check the cast result and add the sounds appropriately
			if (p) {
				if (p->getCharacter().name == "Lez")
					p->setSound(LSconvo1);
				if (p->getCharacter().name == "Sassy")
					p->setSound(LSconvo2);


				times.push_back(0.0f);
				times.push_back(1.5f);

				orders.push_back("Lez");
				orders.push_back("Sassy");

				convos.push_back(times);
				convoOrders.push_back(orders);

				//in the works for future full conversations
				//noOfSounds++;
			}
		}
	}
	if (DonnyCounter == 0)
	{
		//push back clarence, lez and sassy conversations
	}
	if (SassyCounter == 0)
	{
		//push back donny, lez and clarence conversations
	}
	if (LezCounter == 0)
	{
		//push back donny, clarene and sassy conversations
	}
	//set the first wave to be spawned
	currentWave = 0;

#pragma endregion
#pragma region HUD and Text
	//initialise the HUD
	bossHealth = new Image("Assets/Art/BossHealth.png", glm::vec2(0.0f, 700.0f), false);

	//initialise end condition buttons
	quitBtn = new Button(Button::NORMAL, glm::vec2(640.0, 460.0), "Exit", true);
	exitBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Main Menu", true);

	resumeBtn = new Button(Button::NORMAL, glm::vec2(640.0, 460.0), "Resume", true);
	mainMenuBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Quit", true);
	pauseBackground = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));

	waveText = new Text(glm::vec2(600.0, 300.0), "assets/Fonts/Another_.ttf");
	waveText->scale(glm::vec2(2.5f, 2.5f));

	barInfo = new Text(glm::vec2(550.0, 450.0), "assets/Fonts/Another_.ttf");

	bossText = new Text(glm::vec2(550.0, 625.0), "assets/Fonts/Another_.ttf");

	endGameText = new Text(glm::vec2(550.0, 625.0), "assets/Fonts/Another_.ttf");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#pragma endregion
}
#pragma endregion

vector<irrklang::ISoundSource*> Game::loadSounds(string character)
{
	vector<irrklang::ISoundSource*> temp;
	for (int i = 0; i < 3; i++) {
		string tempstr = "assets/Sounds/" + character + "/lines/line" + to_string(i) + ".wav";
		const char* tmpChar = tempstr.c_str();
		irrklang::ISoundSource* tempSource = AmbientEngine->addSoundSourceFromFile(tmpChar); // conversation
		temp.push_back(tempSource);
	}
	return temp;
}

void Game::addCharacterSounds(string charName)
{
	vector<irrklang::ISoundSource*> charSounds = loadSounds(charName);
	for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end(); ++it)
	{
		Player *p = dynamic_cast<Player*>(*it);

		//check the cast result and add the sounds appropriately
		if (p && p->getCharacter().name == charName) 
		{
			//cycle through all the preloaded sounds
			for (int i = 0; i < charSounds.size(); i++)
			{
				//and add them to the player
				p->setSound(charSounds[i]);
			}
		}
	}
}

bool Game::checkCollision(GameObject* a, GameObject* b)
{
	if (abs(a->getCollider()->getPos().x - b->getCollider()->getPos().x) > (a->getCollider()->getHW() + b->getCollider()->getHW())) return false;
	if (abs(a->getCollider()->getPos().z - b->getCollider()->getPos().z) > (a->getCollider()->getHH() + b->getCollider()->getHH())) return false;

	return true;
}

bool Game::checkRayToAABB(glm::vec3* rayPos, glm::vec3* rayDir, GameObject * object)
{
	// Collision Box Minimum point
	glm::vec3 boxMin = glm::vec3(object->getCollider()->getPos().x - object->getCollider()->getHW(),
								 object->getCollider()->getPos().y - object->getCollider()->getTH(),
								 object->getCollider()->getPos().z - object->getCollider()->getHH() );
	// Collision Box Maximum point
	glm::vec3 boxMax = glm::vec3(object->getCollider()->getPos().x + object->getCollider()->getHW(),
								 object->getCollider()->getPos().y + object->getCollider()->getTH(),
								 object->getCollider()->getPos().z + object->getCollider()->getHH() );

	float tmin = (boxMin.x - rayPos->x) / rayDir->x;
	float tmax = (boxMax.x - rayPos->x) / rayDir->x;

	if (tmin > tmax) swap(tmin, tmax);

	float tymin = (boxMin.y - rayPos->y) / rayDir->y;
	float tymax = (boxMax.y - rayPos->y) / rayDir->y;

	if (tymin > tymax) swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (boxMin.z - rayPos->z) / rayDir->z;
	float tzmax = (boxMax.z - rayPos->z) / rayDir->z;

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	return true;
}

void Game::generateWave(int waveNumber)
{
	//check if an enemy is due to be spawned, and if so create it
	while (waveCounters.at(waveNumber) > 0) {
		waveSpawner->spawnEnemy(mapWaves.at(waveNumber), gameObjects);
		waveCounters.at(waveNumber)--;
	}

}

#pragma region Update
void Game::update()
{
	//to prevent updates running before everything has loaded
	if (isGameRunning == true && initialised)
	{
		// if not already playing
		if (ambientInitialised == false) {
			//set up sound
			AmbientEngine->setSoundVolume(0.03f);
			AmbientEngine->play2D("assets/Sounds/Ambient/AmbientMusic.wav", GL_TRUE);
			ambientInitialised = true;
		}

		//set up timing 
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		//update the conversation timers
		conversationUpdate();

		//check if there are no players/enemies left 
		for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end(); ++it)
		{
			Boss* tmp = dynamic_cast<Boss*>(*it);
			Enemy* tmp1 = dynamic_cast<Enemy*>(*it);
			Player* tmp2 = dynamic_cast<Player*>(*it);
			if (tmp && tmp->getHealth() > 0 || tmp1 && tmp1->getDeath() == false)
				enemyCounter++;
			if (tmp2 && tmp2->getDeath() == false)
				playerCounter++;

		}

		//if there are no players left alive
		if (playerCounter < 1)
		{
			//lose conditions
			isGameRunning = false;
			gameLost = true;
			glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		}else
		//if an enemy was not detected
		if (enemyCounter <= 0)
		{
			if (currentWave > 6)
			{
				//victory conditions
				isGameRunning = false;
				gameWon = true;
				glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}

			waveTimer -= deltaTime;
			transparency += deltaTime;
			//if the wave has not been initialised yet, initialise the wave change sound and volume
			if (waveInitialised == false) {
				AmbientEngine->setSoundVolume(0.065f);//wave
				AmbientEngine->play2D("assets/Sounds/Ambient/WaveChange.wav", GL_FALSE);
				waveInitialised = true;
			}
			//draw the wave notification text
			waveText->draw("Wave " + std::to_string(currentWave + 1) + "...", glm::vec4(1.0f, 1.0f, 1.0f, textAlpha), 1);
			if (currentWave > 0) {
				if (textAlpha > 0.0f)
					textAlpha = 6.0f - transparency;
			}
			else {
				//account for the drastic slowdown at the start of compilation
				if (textAlpha > 0.0f)
					textAlpha -= 0.001f;
			}
		}
		else
		{
			//reset everything for the next wave
			waveInitialised = false;
			textAlpha = 1.0f;
			transparency = 0.0f;
		}

		//re-zero the value for checking next frame
		enemyCounter = 0;

		//if the timer has hit zero, spawn the current wave
		if (waveTimer <= 0) {
			generateWave(currentWave);
			waveTimer = 10.0f;
			currentWave++;
		}

		//check if the player has won the game
		if (currentWave > mapWaves.size())
			gameWon = true;

		//enemy and boss update loop
		for (int i = 0; i < gameObjects.size(); i++) {
			if (gameObjects[i] != nullptr) {
				gameObjects[i]->componentUpdate();
				gameObjects[i]->update();
				//update enemy AI 
				Enemy *e = dynamic_cast<Enemy*>(gameObjects[i]);
				if (e)
				{
					e->update();
				}

				//update the boss health and path finding attributes
				Boss *b = dynamic_cast<Boss*>(gameObjects[i]);
				if (b)
				{
					bossHealth->scale(glm::vec2(b->getHealth(), 20.0f), false);
					bossHealth->draw();
					bossText->draw("Bumble-Brutus", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1);
					b->update();
					b->checkFieldEmpty(gameObjects);
					b->spawnMinions(gameObjects, toonShader, pathManager);
				}
			}
		}

#pragma region Collision Loop
		//collision checking loop
		for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end() - 1; ++it)
		{
			for (vector<GameObject*>::iterator it1 = it + 1; it1 < gameObjects.end(); ++it1) // we make sure that we check a collision between the same objcts only once
			{
				if ((*it)->getCollider() && (*it1)->getCollider()) {

					if (checkCollision((*it), (*it1)) == true)
					{
						//use dynamic casting to find out what is colliding with what
						e1 = dynamic_cast<Enemy*>(*it);
						e2 = dynamic_cast<Enemy*>(*it1);
						p1 = dynamic_cast<Player*>(*it);
						p2 = dynamic_cast<Player*>(*it1);
						ob1 = dynamic_cast<Obstacle*>(*it);
						ob2 = dynamic_cast<Obstacle*>(*it1);
						pr1 = dynamic_cast<Prop*>(*it);
						pr2 = dynamic_cast<Prop*>(*it1);

						//player - bar collision
						if (p1 && pr1 || p2 && pr2 || p1 && pr2 || p2 && pr1)
						{
							if (p1)
								barInteraction(p1);
							else
								barInteraction(p2);
						}
						else
						//player - wall collision
						if (p1 && ob1 || p2 && ob2 || p1 && ob2 || p2 && ob1)
						{
							if (p1)
								p1->Move(-p1->getPreviousPosition());
							else
								p2->Move(-p2->getPreviousPosition());
						}else
						//player, enemy collision
						if (e1 && p2 || e2 && p1 || e2 && p2 || p1 && e1)
						{
							playerEnemyCollision((*it), (*it1));
						}
					}
				}
			}

		}

#pragma endregion

		// Player Attacking
		for (int i = 0; i < playerList.size(); i++) {
			if (playerList[i] != nullptr) {
				if (playerList[i]->hasPlayerAttacked()) {

					//play the gunshot noise
					AmbientEngine->play2D("assets/Sounds/gun.wav"); // conversation

					//iterate through game objects and find an enemy
					for (int j = 0; j < gameObjects.size(); j++) {
						Enemy *e = dynamic_cast<Enemy*>(gameObjects[j]);
						if (e) {
							//check for an intersection and take damage if so
							if (checkRayToAABB(&playerList[i]->getPosition(), &playerList[i]->getCamera()->getCameraFront(), (e)))
							{
								e->takeDamage(10.0f);
								if (e->getDeath() == true)
									playerList[i]->gainPoints(25);
								else
									playerList[i]->gainPoints(5);
								
							}
						}
						//do the same for the boss
						Boss *b = dynamic_cast<Boss*>(gameObjects[j]);
						if (b) {
							if (checkRayToAABB(&playerList[i]->getPosition(), &playerList[i]->getCamera()->getCameraFront(), (b)))
							{
								b->takeDamage(1000.0f);
								if (b->getHealth() <= 0)
									playerList[i]->gainPoints(250);
								else
									playerList[i]->gainPoints(12);
							}

						}
					}
				}
			}
		}
	}
	
	//pause button
	if (Input::keyboard1.keys[GLFW_KEY_P])
	{
		//stop running the gameloop
		isGameRunning = false;	
		g_window = glfwGetCurrentContext();
		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	//if the game is paused
	if (isGameRunning == false) 
	{

		//loop through and set all the objects to paused
		vector<GameObject*>::iterator it;
		for (it = gameObjects.begin(); it != gameObjects.end(); it++)
		{
			(*it)->setPaused(true);
		}
		
		//if the game is unpaused do the opposite and restart the game loop
		if (resumeBtn->buttonClick()) 
		{
			vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				(*it)->setPaused(false);
			}
			isGameRunning = true;
			glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		//end the program if the main menu button is selected
		if (mainMenuBtn->buttonClick()) 
		{
			glfwDestroyWindow(g_window);
			exit(0);
		}

	}

	//update one path per frame so the computer doesnt melt
	if (pathManager->working == false) {
		pathManager->update(gameObjects, toonShader);
	}
	if (pathManager->working == true)
		pathManager->working = false;

}
#pragma endregion

void Game::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// viewports
	int playerCount = 0;
	glViewport(0, 0, Input::SCREEN_WIDTH, Input::SCREEN_HEIGHT);

	// Check whether splitscreen or not
	if (playerList[1] != nullptr) {
		glViewportIndexedf(0, 0, Input::SCREEN_HEIGHT / 2, Input::SCREEN_WIDTH, Input::SCREEN_HEIGHT / 2);
		glViewportIndexedf(1, 0, 0, Input::SCREEN_WIDTH, Input::SCREEN_HEIGHT / 2);
		playerCount = 2;
	}
	else {
		playerCount = 1;
	}

	for (int k = 0; k < playerCount; k++)
	{
		glm::mat4 projection = (glm::perspective(float(glm::radians(60.0f)), 1280.0f / 720.0f, 1.0f, 150.0f)); 

		//pass material and position variables to the shader
		glUseProgram(toonShader->getID());
		glUniform1i(glGetUniformLocation(toonShader->getID(), "viewportNum"), k);
		glUniformMatrix4fv(glGetUniformLocation(toonShader->getID(), "mvp_matrix"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform1i(glGetUniformLocation(toonShader->getID(), "material.diffuse1"), diffuse);
		glUniform1i(glGetUniformLocation(toonShader->getID(), "material.specular1"), specular);
		glUniform1f(glGetUniformLocation(toonShader->getID(), "material.shininess"), shininess);
		glUniform3f(glGetUniformLocation(toonShader->getID(), "viewPos"), playerList[k]->getCamera()->getCameraPos().x, playerList[k]->getCamera()->getCameraPos().y, playerList[k]->getCamera()->getCameraPos().z);
		// draw skybox
		skybox->draw(projection * glm::mat4(glm::mat3(playerList[k]->getCamera()->lookAtMat())), k);

		//if the game is paused
		if (isGameRunning == false && gameWon == false && gameLost == false)
		{
			// Draws pause menu
			resumeBtn->draw();
			mainMenuBtn->draw();
			pauseBackground->draw();
			glEnable(GL_DEPTH_TEST);
		}

		//game end state
		if (isGameRunning == false && gameWon == true || gameLost == true) {

			if (gameWon == true) {
				bossText->draw("You Win!", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1);
			}
			if (gameLost == true) {
				bossText->draw("You Lose...", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1);
			}
			exitBtn->draw();
			quitBtn->draw();
			glEnable(GL_DEPTH_TEST);

			//close the program if the player clicks exit
			if (exitBtn->buttonClick())
			{
				glfwDestroyWindow(g_window);
				exit(0);
			}
		}
		//loop through the gameobjects and draw 
		for (int i = 0; i < gameObjects.size(); i++) {
			if (gameObjects[i] != nullptr) {
				gameObjects[i]->componentDraw(playerList[k]->getCamera()->lookAtMat());
			}
		}
	}
}

void Game::playerEnemyCollision(GameObject* a, GameObject* b)
{
	//to get the objects from the gameobjects
	Player* p;
	Enemy* e;

	//first find out which one is which
	if (dynamic_cast<Enemy*>(a))
	{
		p = dynamic_cast<Player*>(b);
		e = dynamic_cast<Enemy*>(a);
	}
	else
	{
		p = dynamic_cast<Player*>(a);
		e = dynamic_cast<Enemy*>(b);
	}

	//check if the enemy can attack, and if so, do.
	if (e->canAttack() == true) {
		p->takeDamage(15.0f);
		e->Attacked(true);
	}

	//stop the choomah from moving whilst attacking a player and set his attack animation
	e->setMoving(false);
	if (!e->getInjured() && !e->getDeath()) {
		if (e->getName() == "normal")
			e->setAnimValues(3.75f, 1.36f);
		if (e->getName() == "charger")
			e->setAnimValues(10.83f, 1.1f);
		if (e->getName() == "brawler")
			e->setAnimValues(2.25f, 1.35f);
	}
}

void Game::barInteraction(Player* p)
{
	barInfo->move(glm::vec2(550.0f, 450.0f));
	barInfo->draw("Press X to refill ammo : 50", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	barInfo->move(glm::vec2(550.0f, 415.0f));
	barInfo->draw("Press Y to refill health : 100", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	barInfo->move(glm::vec2(550.0f, 380.0f));
	barInfo->draw("Press B to upgrade weapon : 450", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1);

	if (Input::keyboard1.keys[GLFW_KEY_X])
	{
		if (p->getPoints() >= 50)
		{
			//do ammo refil
		}
	}

	if (Input::keyboard1.keys[GLFW_KEY_Y])
	{
		if (p->getPoints() >= 100)
		{
			//do health refil
			p->setHealth(50);
		}
	}

	if (Input::keyboard1.keys[GLFW_KEY_B])
	{
		//change weapon stats here
	}
}

void Game::conversationUpdate()
{
	//timing for speech calls to prevent characters talking over each other too much
	if (conversationTimer > 0)
	{
		conversationTimer -= deltaTime;
	}
	else {

		//get random sound and play it
		srand(time(0));
		int randomSound = rand() % noOfSounds;

		int orderPlace = 0;
		int count = 0;
		//iterate through the current objects
		for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end(); ++it)
		{
			count++;
			int check = 0;
			//if the random sound is less than three (sounds involving only one character)
			if (randomSound < 3)
			{
				check = 1;
			}
			else
			{
				check = convoOrders.at(randomSound).size();
			}

			//assign sounds according to each character
			Player *p = dynamic_cast<Player*>(*it);
			if (p && p->getCharacter().name == convoOrders.at(randomSound).at(orderPlace)) {
				if (p->getCharacter().name == "Sassy")
					randomSound -= 3;
				if (p->getCharacter().name == "Donny")
					randomSound -= 6;
				p->playSound(randomSound, convos.at(randomSound).at(orderPlace));
				orderPlace++;
				if (orderPlace == check)
					break;
			}

			//if not all the characters have had their sounds assigned
			if (count == gameObjects.size() && orderPlace < check)
			{
				//restart the loop
				it = gameObjects.begin();
				count = 0;
			}


		}
		//reset the timer for 15 seconds
		conversationTimer = 15.0f;
	}
}