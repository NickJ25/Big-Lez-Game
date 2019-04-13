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

// Initalize Two Camera
//Camera lezCamera(glm::vec3(110.0f, 12.5f, 190.0f), FREECAM);

rt3d::materialStruct material0 = {
	{0.0f, 0.8f, 0.2f, 1.0f}, // ambient
	{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
	{0.0f, 0.1f, 0.0f, 1.0f}, // specular
	2.0f  // shininess
};

int diffuse = 0;
int specular = 1;
float shininess = 32.0f;


void Game::createPlayers()
{
	for (int i = 0; i < GameData::g_PlayerData.size(); i++) {
		if (GameData::g_PlayerData[i] != nullptr) {
			playerList[i] = new Player(GameData::g_PlayerData[i]->control, *GameData::g_PlayerData[i], glm::vec3(0.0f, 0.0f, 0.0f));
			playerList[i]->setShader(toonShader);
			playerList[i]->addCollision(glm::vec3(45.0f, -12.5f, 20.0f), 5.0f, 5.0f);
			gameObjects.push_back(playerList[i]);
		}
	}
}

void Game::createWeapons()
{
	for (int i = 0; i < playerList.size(); i++) {
		switch (playerList[i]->getCharacter().name) {

		}
	}
}

void Game::init()
{
	std::cout << "Game.cpp Init" << std::endl;
	toonShader = new Shader("src/toonShader.vert", "src/toonShader.frag");

	skybox = new Skybox("assets/Skybox/back.bmp", "assets/Skybox/front.bmp",
		"assets/Skybox/right.bmp", "assets/Skybox/left.bmp",
		"assets/Skybox/top.bmp", "assets/Skybox/bottom.bmp");

	showBoundingBoxes = false;

	////	Init Objects	////
	GameObject* dirLight = new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.9f, 0.9f, 0.9f));
	dirLight->setShader(toonShader);
	gameObjects.push_back(dirLight);

	//GameObject* spotLight = new SpotLight(mainCamera->getCameraPos(), mainCamera->getCameraFront(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.1f), 0.4, 3);
	//spotLight->setShader(toonShader);
	//gameObjects.push_back(spotLight);
	//GameObject* pointLight = new PointLight(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.09f, 0.05f, 0.09f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.32f));
	//pointLight->setShader(toonShader);
	//gameObjects.push_back(pointLight);

	//GameObject* table = new Prop("assets/Props/Table/table.obj", glm::vec3(0.0f, 0.0f, 0.0f));
	//table->setShader(toonShader);
	//gameObjects.push_back(table);
	//GameObject* couch = new Prop("assets/Props/Couch/couch.obj", glm::vec3(5.0f, 0.0f, 5.0f));
	//couch->setShader(toonShader);
	//gameObjects.push_back(couch);

	GameObject* environment = new Prop("assets/Props/Map/envMap1.dae", glm::vec3(0.0f, 20.0f, 100.0f));
	environment->setShader(toonShader);
	environment->Move(glm::vec3(0.0f, 60.0f, 0.0f));
	gameObjects.push_back(environment);

	createPlayers();

	// Characters
	Player::Character BigLez;
	BigLez.fileLocation = "assets/Characters/BigLez/lez.dae";
	BigLez.name = "Lez";
	BigLez.health = 100;
	BigLez.walkSpeed = 10;

	Player::Character Sassy;
	Sassy.fileLocation = "assets/Characters/Sassy/sassy.dae";
	Sassy.name = "Sassy";

	Player::Character cube;
	cube.fileLocation = "assets/Props/Map/gridblock.dae";
	cube.name = "boundingbox";

	//Player::Character doorCollider;
	//cube.fileLocation = "assets/Props/Map/gridblock.dae";
	//cube.name = "doorbox";

	//GameObject* bigLez = new Player(doorCollider);
	//bigLez->setShader(toonShader);
	//bigLez->setAnim(0);
	//bigLez->Move(glm::vec3(45.0f, -12.5f, -26.0f));
	//bigLez->addCollision(glm::vec3(45.0f, -12.5f, -26.0f), 1.0f, 1.0f);
	//gameObjects.push_back(bigLez);


	sassy = new Player(Input::CONTROLLER1, Sassy, glm::vec3(45.0f, -12.5f, 20.0f)); // Change to prop is issue?
	sassy->setShader(toonShader);
	sassy->Move(glm::vec3(45.0f, -12.5f, 20.0f));
	sassy->setAnimation(5.0f, 1.0f);
	sassy->addCollision(glm::vec3(45.0f, -12.5f, 20.0f), 5.0f, 5.0f);
	gameObjects.push_back(sassy);

	//mainPlayer = new Player(Input::KEYBOARD, BigLez, glm::vec3(45.0f, -12.5f, 20.0f));
	//mainPlayer->setShader(toonShader);
	//mainPlayer->Move(glm::vec3(45.0f, -12.5f, 20.0f));
	////mainPlayer->setStill(true);
	//mainPlayer->addCollision(glm::vec3(45.0f, -12.5f, 20.0f), 5.0f, 5.0f);
	//gameObjects.push_back(mainPlayer);

	GameObject* lezShotgun = new Gun("assets/Weapons/Shotgun/lezshotgun.dae", "Shotgun", 8, 8, 1.0, false);
	lezShotgun->setShader(toonShader);
	lezShotgun->setAnimation(0.0f, 1.0f);
	//mainPlayer->addWeapon(dynamic_cast<Weapon*> (lezShotgun)); 
	playerList[0]->addWeapon(dynamic_cast<Weapon*> (lezShotgun));
	gameObjects.push_back(lezShotgun);

	//GameObject* lezTest = new Prop("assets/Props/Table/Table.dae", glm::vec3(0.0f, 0.0f, 0.0f), "NoBounding");
	//lezTest->Move(glm::vec3(-10.0f, 0.0f, -10.0f));
	//cout << "lez test pos:" << lezTest->getPosition().x << " " << lezTest->getPosition().y << " " << lezTest->getPosition().z << "----------------------" << endl;
	//lezTest->setShader(toonShader);
	//lezTest->Rotate(-90.0f, glm::vec3(1.0, 0.0, 0.0));
	//lezTest->addCollision(glm::vec3(-10.0f, 0.0f, -10.0f), 50, 50);
	//gameObjects.push_back(lezTest);


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
	rightDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(100.0f, -12.5f, 32.0f), glm::vec3(80.0f, -12.5f, 32.0f)));


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

	//prepare wave 1 to be spawned
	//for (int i = 0; i < 5; i++) { 
	//	waveSpawner->spawnWave(gameObjects, 0, toonShader, pathManager, false);
	//}
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

				noOfSounds++;
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

	//initialise the HUD
	bossHealth = new Image("Assets/Art/BossHealth.png", glm::vec2(0.0f, 700.0f), false);

	resumeBtn = new Button(Button::NORMAL, glm::vec2(640.0, 460.0), "Resume");
	mainMenuBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Quit");
	pauseBackground = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));

	testtxt = new Text(glm::vec2(590.0, 445.0), "assets/Fonts/Another_.ttf");
	testtxt2 = new Text(glm::vec2(600.0, 325.0), "assets/Fonts/Another_.ttf");

	waveText = new Text(glm::vec2(600.0, 300.0), "assets/Fonts/Another_.ttf");
	waveText->scale(glm::vec2(2.5f, 2.5f));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

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

	//penetrationDepthX = a->getCollider()->getHW() + b->getCollider()->getHW() - a->getCollider()->getPos().x - b->getCollider()->getPos().x;
	//penetrationDepthZ = a->getCollider()->getHH() + b->getCollider()->getHW() - a->getCollider()->getPos().z - b->getCollider()->getPos().z;

	return true;
}

//bool Game::checkRayToAABB(glm::vec3* rayPos, glm::vec3* rayDir, GameObject * object)
//{	
//	// Prerequisites
//	vector<float>t_rayPos = { rayPos->x, rayPos->y, rayPos->z};
//	vector<float>t_rayDir = { rayDir->x, rayDir->y, rayDir->z };
//	vector<float>t_min = { object->getCollider()->getPos().x - object->getCollider()->getHW(),
//							object->getCollider()->getPos().y - object->getCollider()->getTH(),
//							object->getCollider()->getPos().z - object->getCollider()->getHH() };
//	vector<float>t_max = { object->getCollider()->getPos().x + object->getCollider()->getHW(),
//							object->getCollider()->getPos().y + object->getCollider()->getTH(),
//							object->getCollider()->getPos().z + object->getCollider()->getHH() };
//
//	// For all three slabs
//	for (int i = 0; i < 3; i++) {
//		float tmin = 0.0f;
//		float tmax = FLT_MAX;
//		if (abs(t_rayDir[i]) < std::numeric_limits<float>::epsilon()) {
//			if (t_rayPos[i] < t_min[i] || t_rayPos[i] > t_max[i]) return 0;
//		}
//		else {
//			// Compute intersection t value of ray with near and far plane of slab
//			float ood = 1.0f / t_rayDir[i];
//			float t1 = (t_min[i] - t_rayPos[i]) * ood;
//			float t2 = (t_max[i] - t_rayPos[i]) * ood;
//			// Make t1 be intersection with near plane, t2 with far plane
//			if (t1 > t2) {
//				float temp;
//				temp = t2;
//				t1 = t2;
//				t1 = temp;
//			}
//			// Compute the intersection of slab intersection intervals
//			if (t1 > tmin) tmin = t1;
//			if (t2 > tmax) tmax = t2;
//			//Exit with no collision as soon as slab intersection becomes empty
//		}
//	}
//	return 1;
//}

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

bool Game::pointIsAbovePlane(const glm::vec3 & P, const glm::vec3 & n, float d)
{
	return glm::dot(n, P) + d > FLT_EPSILON;
}

char Game::computePointMask(glm::vec3 p, Enemy* e)
{
	glm::vec3 center = p;
	glm::vec2 radii = glm::vec2(e->getCollider()->getHW(), e->getCollider()->getHH());

	char mask = 0;
	if (pointIsAbovePlane(p, nright, -center.x - radii.x))
	{
		mask |= 1;// +x
	}
	if (pointIsAbovePlane(p, nleft, center.x - radii.x))
	{
		mask |= 2;	// -x
	}
	if (pointIsAbovePlane(p, nup, -center.z - radii.y))
	{
		mask |= 4;	// +y
	}
	if (pointIsAbovePlane(p, ndown, center.z - radii.y))
	{
		mask |= 8;	// -y
	}
	return mask;
}

glm::vec3 Game::getFaceNormal(glm::vec3 p, Enemy* e)
{
	char mask = computePointMask(p, e);
	glm::vec3 normal = glm::vec3(0, 0, 0);
	if ((mask & 1) == 1)	// +x
	{
		normal += nright;
	}
	if ((mask & 2) == 2)	// -x
	{
		normal += nleft;
	}
	if ((mask & 4) == 4)	// +y
	{
		normal += nup;
	}
	if ((mask & 8) == 8)	// -y
	{
		normal += ndown;
	}
	return normalize(normal);
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

void Game::update()
{
	if(isGameRunning == true && initialised)
	{
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
				for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end(); ++it)
				{
					count++;
					int check = 0;
					if (randomSound < 3)
					{
						check = 1;
					}
					else
					{
						check = convoOrders.at(randomSound).size();
					}
					

					Player *p = dynamic_cast<Player*>(*it);
					if (p && p->getCharacter().name == convoOrders.at(randomSound).at(orderPlace)) {
						p->playSound(randomSound, convos.at(randomSound).at(orderPlace));
						orderPlace++;
						if (orderPlace == check)
							break;
					}

					if (count == gameObjects.size() && orderPlace < check)
					{
						it = gameObjects.begin();
						count = 0;
					}


				}

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
			if (waveInitialised == false) {
				WaveEngine->setSoundVolume(0.075f);
				WaveEngine->play2D("assets/Sounds/Ambient/WaveChange.wav", GL_FALSE);
				waveInitialised = true;
			}
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

				Boss *b = dynamic_cast<Boss*>(gameObjects[i]);
				if (b)
				{
					bossHealth->scale(glm::vec2(b->getHealth(), 20.0f), false);
					bossHealth->draw();
					b->update();
					b->checkFieldEmpty(gameObjects);
					b->spawnMinions(gameObjects, toonShader, pathManager);
				}
			}
		}

		//collision checking loop
		for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end() - 1; ++it)
		{
			for (vector<GameObject*>::iterator it1 = it + 1; it1 < gameObjects.end(); ++it1) // we make sure that we check a collision between the same objcts only once
			{
				if ((*it)->getCollider() && (*it1)->getCollider()) {

					//if it is a player and a wall
					Player *p1 = dynamic_cast<Player*>((*it));
					Player *p2 = dynamic_cast<Player*>((*it1));
					Obstacle *o1 = dynamic_cast<Obstacle*>((*it));
					Obstacle *o2 = dynamic_cast<Obstacle*>((*it1));

					if (checkCollision((*it), (*it1)) == true)
					{



						if (o1 && p2 || p1 && o2)
						{
							cout << "colliding" << endl;
						}

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
	/*						if (e1)
							{
								e1->setMoving(false);
								if(!e1->getInjured())
								e1->setAnimValues(3.6f, 1.36);
							}
							if (e2)
							{
								e2->setMoving(false);
								if (!e2->getInjured())
								e2->setAnimValues(3.6f, 1.36);
							}*/
							
						}
					}
				}
			}
		}
		// Player Attacking
		if(playerList[0]->hasPlayerAttacked()) cout << "FIRE ZE MISSILES!" << endl;

		for (int i = 0; i < gameObjects.size(); i++) {
			Enemy *e = dynamic_cast<Enemy*>(gameObjects[i]);
			if (e) {
				cout << "C_Area: " << e->getCollider()->getPos().x << " " << e->getCollider()->getPos().y << " " << e->getCollider()->getPos().z << endl;
				cout << "P_Player: " << playerList[0]->getPosition().x << " " << playerList[0]->getPosition().y << " " << playerList[0]->getPosition().z << endl;
				cout << "AABB: " << checkRayToAABB(&playerList[0]->getPosition(), &playerList[0]->getCamera()->getCameraFront(), (e)) << endl;
			}

		}

	}
	
	if (Input::keyboard1.keys[GLFW_KEY_P])
	{
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
			ableTo == true;
			/*if (clicked == false) {
				removeEnemies(gameObjects);
				clicked = true;
			}*/
		}

		//reset function for remove enemies
		if (Input::keyboard1.keys[GLFW_KEY_N])
		{
			if (clicked == true) {
				clicked = false;
			}
		}
#pragma endregion

	if (isGameRunning == false) 
	{
		vector<GameObject*>::iterator it;
		for (it = gameObjects.begin(); it != gameObjects.end(); it++)
		{
			(*it)->setPaused(true);
		}
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

		if (mainMenuBtn->buttonClick()) 
		{
			glfwDestroyWindow(g_window);
			exit(0);
		}

	}

	if (Input::keyboard1.keys[GLFW_KEY_Q]) {

		vector<GameObject*>::iterator it;
		for (it = gameObjects.begin(); it != gameObjects.end(); it++)
		{
			(*it)->setPaused(true);

			Enemy *tmp = dynamic_cast<Enemy*>(*it);
			if (tmp != nullptr) {
				tmp->setPaused(true);
			}
		}
	}

	if (Input::keyboard1.keys[GLFW_KEY_E]) {

		vector<GameObject*>::iterator it;
		for (it = gameObjects.begin(); it != gameObjects.end(); it++)
		{
			(*it)->setPaused(false);

			Enemy *tmp = dynamic_cast<Enemy*>(*it);
			if (tmp != nullptr) {
				tmp->setPaused(false);
			}

		}
	}


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

	//if (Input::keyboard1.keys[GLFW_KEY_X]) {
	//	mainPlayer->playAnimation();
	//}

	if (Input::keyboard1.keys[GLFW_KEY_M]) {

		if (takeDamage == false) {
			vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				Enemy *tmp = dynamic_cast<Enemy*>(*it);
				if (tmp)
				{
					tmp->takeDamage(0.05f);
				}
			}
			takeDamage = true;
		}
	}

	if (Input::keyboard1.keys[GLFW_KEY_O]) {

		if (takeDamage == true) {
			takeDamage = false;
		}
	}

	//update one path per frame so the computer doesnt melt
	if (pathManager->working == false) {
		pathManager->update(gameObjects, toonShader);
	}
	if (pathManager->working == true)
		pathManager->working = false;

	const Uint8 *keys = SDL_GetKeyboardState(NULL); /// ----------------------------------------------------------------------REMOVE
	if (keys[SDL_SCANCODE_ESCAPE]) SDL_SetRelativeMouseMode(SDL_FALSE); // TEMP
	else SDL_SetRelativeMouseMode(SDL_TRUE);
}


void Game::draw()
{
	//glEnable(GL_DEPTH_TEST);
	glUseProgram(toonShader->getID());
	glUniform1i(glGetUniformLocation(toonShader->getID(), "material.diffuse1"), diffuse);
	glUniform1i(glGetUniformLocation(toonShader->getID(), "material.specular1"), specular);
	glUniform1f(glGetUniformLocation(toonShader->getID(), "material.shininess"), shininess);
\
	glUniform3f(glGetUniformLocation(toonShader->getID(), "viewPos"), playerList[0]->getCamera()->getCameraPos().x, playerList[0]->getCamera()->getCameraPos().y, playerList[0]->getCamera()->getCameraPos().z);
	glm::mat4 projection = (glm::perspective(float(glm::radians(60.0f)), 1280.0f / 720.0f, 1.0f, 150.0f));

	skybox->draw(projection * glm::mat4(glm::mat3(playerList[0]->getCamera()->lookAtMat())));


	if (isGameRunning == false)
	{
		// Draws pause menu
		resumeBtn->draw();
		mainMenuBtn->draw(); 
		testtxt->draw("Resume", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),1);
		testtxt2->draw("Quit", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),1);
		pauseBackground->draw();
	}

	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i] != nullptr) {
			gameObjects[i]->componentDraw(playerList[0]->getCamera()->lookAtMat());
		}
	}
	
}
