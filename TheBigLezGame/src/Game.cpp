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
			playerList[i] = new Player(GameData::g_PlayerData[i]->control, *GameData::g_PlayerData[i], glm::vec3(0.0f, 0.0f, 0.0f));
			assignAttributes(i);
			playerList[i]->setShader(toonShader);
			playerList[i]->addCollision(glm::vec3(45.0f, -12.5f, 20.0f), 5.0f, 5.0f);
			gameObjects.push_back(playerList[i]);
		}
	}
}

void Game::createWeapons()
{
	for (int i = 0; i < playerList.size(); i++) {
		if (playerList[i] != nullptr) {
			switch (playerList[i]->getCharacter().id) {
			case 1: // Gun Setup for BigLez
			{
				GameObject* lezShotgun = new Gun("assets/Weapons/Shotgun/lezshotgun.dae", "Shotgun", 8, 8, 1.0, false);
				lezShotgun->setShader(toonShader);
				lezShotgun->setAnimation(0.0f, 1.0f);
				playerList[i]->addWeapon(dynamic_cast<Weapon*> (lezShotgun));
				gameObjects.push_back(lezShotgun);

				break;
			}
			case 2: // Gun Setup for Sassy
			{
				cout << "------------------------------------s guns" << "\n";
				break;
			}
			case 3: // Gun Setup for Donny
			{
				cout << "------------------------------------d guns" << "\n";
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

	createPlayers();
	createWeapons();

	

	//// Characters
	//Player::Character BigLez;
	//BigLez.fileLocation = "assets/Characters/BigLez/lez.dae";
	//BigLez.name = "Lez";
	//BigLez.health = 100;
	//BigLez.walkSpeed = 10;

	//Player::Character Sassy;
	//Sassy.fileLocation = "assets/Characters/Sassy/sassy.dae";
	//Sassy.name = "Sassy";

	//Player::Character cube;
	//cube.fileLocation = "assets/Props/Map/gridblock.dae";
	//cube.name = "boundingbox";

	//sassy = new Player(Input::CONTROLLER1, Sassy, glm::vec3(45.0f, -12.5f, 20.0f)); // Change to prop is issue?
	//sassy->setShader(toonShader);
	//sassy->Move(glm::vec3(45.0f, -12.5f, 20.0f));
	//sassy->setAnimation(5.0f, 1.0f);
	//sassy->addCollision(glm::vec3(45.0f, -12.5f, 20.0f), 5.0f, 5.0f);
	//gameObjects.push_back(sassy);

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

		////house in the middle 3.5 til 28
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
	wave1.push_back(0), wave1.push_back(0), wave1.push_back(0), wave1.push_back(1); 
	wave2.push_back(1), wave2.push_back(0), wave2.push_back(0), wave2.push_back(0); 
	wave3.push_back(1), wave3.push_back(0), wave3.push_back(0), wave3.push_back(0); 
	wave4.push_back(1), wave4.push_back(0), wave4.push_back(0), wave4.push_back(0); 
	wave5.push_back(1), wave5.push_back(0), wave5.push_back(0), wave5.push_back(0); 
	wave6.push_back(1), wave6.push_back(0), wave6.push_back(0), wave6.push_back(0);
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

	while(firstWave.size() < 1) { 
		waveSpawner->spawnWave(gameObjects, 0, toonShader, pathManager, true, firstWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;
	while (secondWave.size() < 1)
	{
		waveSpawner->spawnWave(gameObjects, 1, toonShader, pathManager, true, secondWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;
	while (thirdWave.size() < 1)
	{
		waveSpawner->spawnWave(gameObjects, 2, toonShader, pathManager, true, thirdWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;
	while (fourthWave.size() < 1)
	{
		waveSpawner->spawnWave(gameObjects, 3, toonShader, pathManager, true, fourthWave);
		waveCount++;
	}
	waveCounters.push_back(waveCount);
	waveCount = 0;
	while (fifthWave.size() < 1)
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
		irrklang::ISoundSource* LSconvo1 = conversationEngine->addSoundSourceFromFile("assets/Sounds/Lez/LezSassy1.wav");
		irrklang::ISoundSource* LSconvo2 = conversationEngine->addSoundSourceFromFile("assets/Sounds/Sassy/LezSassy1.wav");
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

	resumeBtn = new Button(Button::NORMAL, glm::vec2(640.0, 460.0), "Resume");
	mainMenuBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Quit");
	pauseBackground = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));

	testtxt = new Text(glm::vec2(590.0, 445.0), "assets/Fonts/Another_.ttf");
	testtxt2 = new Text(glm::vec2(600.0, 325.0), "assets/Fonts/Another_.ttf");

	waveText = new Text(glm::vec2(600.0, 300.0), "assets/Fonts/Another_.ttf");
	waveText->scale(glm::vec2(2.5f, 2.5f));

	bossText = new Text(glm::vec2(550.0, 625.0), "assets/Fonts/Another_.ttf");

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
		irrklang::ISoundSource* tempSource = conversationEngine->addSoundSourceFromFile(tmpChar);
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

void removeEnemies(std::vector<GameObject*> & gameObjects)
{
	std::vector<GameObject*>::iterator it = gameObjects.begin();
	while(it != gameObjects.end())
	{

		Enemy* e = dynamic_cast<Enemy*>((*it));
		if (e)
		{
			it = gameObjects.erase(it);
		}
		else {
			++it;
		}
	}
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
	//debug for position
	//cout << "cpos: " << mainPlayer->getCamera()->getCameraPos().x << " , " << mainPlayer->getCamera()->getCameraPos().z << endl;

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

		//check if there are no enemies left 
		for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end(); ++it)
		{
			Boss* tmp = dynamic_cast<Boss*>((*it));
			Enemy* tmp1 = dynamic_cast<Enemy*>((*it));

			if (tmp || tmp1)
				enemyCounter++;
		}

		//if an enemy was not detected
		if (enemyCounter <= 0)
		{

			waveTimer -= deltaTime;
			transparency += deltaTime;
			//if the wave has not been initialised yet, initialise the wave change sound and volume
			if (waveInitialised == false) {
				WaveEngine->setSoundVolume(0.065f);
				WaveEngine->play2D("assets/Sounds/Ambient/WaveChange.wav", GL_FALSE);
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
						//an enemy is colliding with something
						//if it is another enemy
						Enemy *e1 = dynamic_cast<Enemy*>((*it));
						Enemy *e2 = dynamic_cast<Enemy*>((*it1));
						Player *p1 = dynamic_cast<Player*>((*it));
						Player *p2 = dynamic_cast<Player*>((*it1));
						//if there is a player, enemy collision

						if (e1 && p2 || e2 && p1)
						{
							//reimplement when injury animations are all fixed
							//check which one is the enemy, then set to attack animation
							if (p1 && e1) {
								if (e1->canAttack() == true) {
									p1->takeDamage(15.0f);
									e1->Attacked(true);
								}

							}
							if (p1 && e2) {
								if (e2->canAttack() == true) {
									p1->takeDamage(15.0f);
									e2->Attacked(true);
								}

							}
							if (p2 && e1) {
								if (e1->canAttack() == true) {
									p2->takeDamage(15.0f);
									e1->Attacked(true);
								}

							}
							if (p2 && e2) {
								if (e2->canAttack() == true) {
									p2->takeDamage(15.0f);
									e2->Attacked(true);
								}

							}
							if (e1)
							{
								e1->setMoving(false);
								if (!e1->getInjured() && !e1->getDeath()) {
									if (e1->getName() == "normal")
										e1->setAnimValues(3.75f, 1.36f);
									if (e1->getName() == "charger")
										e1->setAnimValues(10.83f, 1.1f);
									if (e1->getName() == "brawler")
										e1->setAnimValues(2.25f, 1.35f);
								}
							}
							if (e2)
							{
								e2->setMoving(false);
								if (!e2->getInjured() && !e2->getDeath()) {
									if (e2->getName() == "normal")
										e2->setAnimValues(3.75f, 1.36f);
									if (e2->getName() == "charger")
										e2->setAnimValues(10.83f, 1.1f);
									if (e2->getName() == "brawler")
										e2->setAnimValues(2.25f, 1.35f);
								}
							}

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
					conversationEngine->play2D("assets/Sounds/gun.wav");

					//iterate through game objects and find an enemy
					for (int j = 0; j < gameObjects.size(); j++) {
						Enemy *e = dynamic_cast<Enemy*>(gameObjects[j]);
						if (e) {
							//check for an intersection and take damage if so
							if (checkRayToAABB(&playerList[i]->getPosition(), &playerList[i]->getCamera()->getCameraFront(), (e)))
							{
								e->takeDamage(10.0f);
							}
						}
						//do the same for the boss
						Boss *b = dynamic_cast<Boss*>(gameObjects[j]);
						if (b) {
							if (checkRayToAABB(&playerList[i]->getPosition(), &playerList[i]->getCamera()->getCameraFront(), (b)))
							{
								b->takeDamage(1000.0f);
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
#pragma region debug tools

	//for testing bounding box locations on the path finding grid and viewing them visually.
	if (Input::keyboard1.keys[GLFW_KEY_1]) {

		if (showBoundingBoxes == false) {
			vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				Player *tmp = dynamic_cast<Player*>(*it);
				if (tmp != nullptr)
				{
					if (tmp->getCharacter().name == "boundingbox")
					{
						if (showBoundingBoxes == false)
							(*it)->setDraw(true);
					}
				}
			}
			showBoundingBoxes = true;
		}
	}

	//undraw debug bounding boxes
	if (Input::keyboard1.keys[GLFW_KEY_2]) {

		if (showBoundingBoxes == true) {
			vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				Player *tmp = dynamic_cast<Player*>(*it);
				if (tmp != nullptr)
				{
					if (tmp->getCharacter().name == "boundingbox")
					{
						(*it)->setDraw(false);
					}
				}
			}
			showBoundingBoxes = false;
		}
	}
	//for testing health bar for the boss
		if (Input::keyboard1.keys[GLFW_KEY_U])
		{
			if (ableTo) {
				for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end(); ++it)
				{
					Boss *b = dynamic_cast<Boss*>(*it);
					if (b)
					{
						b->setHealth(-20.0f);
					}
				}
				ableTo = false;
			}
		}
		//interchangeable - for boss health or uncomment for checking boss waves
		if (Input::keyboard1.keys[GLFW_KEY_B])
		{
			//ableTo == true;
			if (clicked == false) {
				removeEnemies(gameObjects);
				clicked = true;
			}
		}

		//reset function for remove enemies
		if (Input::keyboard1.keys[GLFW_KEY_N])
		{
			if (clicked == true) {
				clicked = false;
			}
		}
#pragma endregion

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
		cout << "1: " << glGetUniformLocation(toonShader->getID(), "viewportNum") << " 2: " << glGetUniformLocation(toonShader->getID(), "mvp_matrix") << "\n";
		glUniformMatrix4fv(glGetUniformLocation(toonShader->getID(), "mvp_matrix"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform1i(glGetUniformLocation(toonShader->getID(), "material.diffuse1"), diffuse);
		glUniform1i(glGetUniformLocation(toonShader->getID(), "material.specular1"), specular);
		glUniform1f(glGetUniformLocation(toonShader->getID(), "material.shininess"), shininess);

		glUniform3f(glGetUniformLocation(toonShader->getID(), "viewPos"), playerList[k]->getCamera()->getCameraPos().x, playerList[k]->getCamera()->getCameraPos().y, playerList[k]->getCamera()->getCameraPos().z);

		// draw skybox
		skybox->draw(projection * glm::mat4(glm::mat3(playerList[k]->getCamera()->lookAtMat())), k);

		//if the game is paused
		if (isGameRunning == false)
		{
			// Draws pause menu
			resumeBtn->draw();
			mainMenuBtn->draw();
			testtxt->draw("Resume", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1);
			testtxt2->draw("Quit", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1);
			pauseBackground->draw();
		}

		//loop through the gameobjects and draw 
		for (int i = 0; i < gameObjects.size(); i++) {
			if (gameObjects[i] != nullptr) {
				gameObjects[i]->componentDraw(playerList[k]->getCamera()->lookAtMat());
			}
		}
	}

	
}
