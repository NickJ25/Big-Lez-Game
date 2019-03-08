#include "Game.h"

vector<GameObject*> gameObjects;
vector<GameObject*> collisionObjs;
Skybox* skybox;
Shader *toonShader;
WaveSpawner* waveSpawner;
Grid* pathFindingGrid;
PathManager* pathManager;

GameObject* sassy;

// Initalize Two Camera
Camera lezCamera(glm::vec3(0.0f, 12.5f, 0.0f), DYNAMIC);

rt3d::materialStruct material0 = {
	{0.0f, 0.8f, 0.2f, 1.0f}, // ambient
	{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
	{0.0f, 0.1f, 0.0f, 1.0f}, // specular
	2.0f  // shininess
};

int diffuse = 0;
int specular = 1;
float shininess = 32.0f;

void Game::init()
{
	mainCamera = &lezCamera;
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


	GameObject* environment = new Prop("assets/Props/Map/envMap.dae", glm::vec3(0.0f, 100.0f, 0.0f));
	environment->setShader(toonShader);
	environment->Move(glm::vec3(0.0f, 100.0f, 0.0f));
	gameObjects.push_back(environment);

	// Characters
	Player::Character BigLez;
	BigLez.fileLocation = "assets/Characters/BigLez/lez.dae";
	BigLez.name = "Leslie";

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


	sassy = new Player(Sassy);
	sassy->setShader(toonShader);
	sassy->Move(glm::vec3(45.0f, -12.5f, 20.0f));
	sassy->setAnimation(0.0f, 6.17f);
	gameObjects.push_back(sassy);


	// add environmental collision boxes for pathfinding an' such
	glm::vec3 fenceScaleVertical = glm::vec3(4.0f, 4.0f, 30.0f);
	glm::vec3 fenceScaleHorizontal = glm::vec3(30.0f, 4.0f, 4.0f);
	glm::vec3 test = glm::vec3(2.5, 2.5, 2.5);
	GameObject* Fence;

	for (int i = 0; i < 20; i++)
	{
		Fence = new Player(cube);
		Fence->setShader(toonShader);
		Fence->setAnimation(0.0f,1.0f);


		glm::vec3 scaleFactor = fenceScaleVertical;
		if (i >= 4 && i < 14) 
			scaleFactor = fenceScaleHorizontal;
		if (i == 14) 
			scaleFactor = glm::vec3(2.0f, 4.0, 25.0f);
		if (i == 15 || i == 16)
			scaleFactor = glm::vec3(18.0f, 4.0, 2.0);
		if (i == 17 || i == 18)
			scaleFactor = glm::vec3(8.0f, 4.0, 2.0);
		if (i == 19)
			scaleFactor = glm::vec3(2.0f, 4.0, 4.0);
			Fence->Scale(scaleFactor);
			
			glm::vec3 pos;

			//fences
			if (i == 0) { Fence->Move(glm::vec3(-13.0f, 0.0f, 0.9f));  pos = glm::vec3(-13.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.9f*scaleFactor.z); 	Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 1) { Fence->Move(glm::vec3(-13.0f, 0.0f, -2.6f));  pos = glm::vec3(-13.0f*scaleFactor.x, 0.0f*scaleFactor.y, -2.6f*scaleFactor.z); 	Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 2) { Fence->Move(glm::vec3(37.0f, 0.0f, 0.9f));  pos = glm::vec3(37.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.9f*scaleFactor.z); 	Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 3) { Fence->Move(glm::vec3(37.0f, 0.0f, -2.6f));  pos = glm::vec3(37.0f*scaleFactor.x, 0.0f*scaleFactor.y, -2.6f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 4) { Fence->Move(glm::vec3(-4.2f, 0.0f, -41.0f));  pos = glm::vec3(-4.2f*scaleFactor.x, 0.0f*scaleFactor.y, -41.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 5) { Fence->Move(glm::vec3(-0.2f, 0.0f, -41.0f));  pos = glm::vec3(-0.2f*scaleFactor.x, 0.0f*scaleFactor.y, -41.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 6) { Fence->Move(glm::vec3(3.2f, 0.0f, -41.0f));  pos = glm::vec3(3.2f*scaleFactor.x, 0.0f*scaleFactor.y, -41.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 7) { Fence->Move(glm::vec3(6.7f, 0.0f, -41.0f));  pos = glm::vec3(6.7f*scaleFactor.x, 0.0f*scaleFactor.y, -41.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

			//house on the right
			if (i == 8) { scaleFactor = fenceScaleVertical; Fence->Move(glm::vec3(50.0f, 0.0f, 0.8f));  pos = glm::vec3(50.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.8f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z+10.0); }
			if (i == 9) { scaleFactor = fenceScaleVertical; Fence->Move(glm::vec3(55.0f, 0.0f, 0.8f));  pos = glm::vec3(55.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.8f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z+10.0); }
			if (i == 10){ scaleFactor = fenceScaleVertical; Fence->Move(glm::vec3(60.0f, 0.0f, 0.8f));  pos = glm::vec3(60.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.8f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z+10.0); }

			//house on the left
			if (i == 11) { Fence->Move(glm::vec3(-5.0f, 0.0f, 0.0f));  pos = glm::vec3(-5.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 12) { Fence->Move(glm::vec3(-5.0f, 0.0f, 5.0f));  pos = glm::vec3(-5.0f*scaleFactor.x, 0.0f*scaleFactor.y, 5.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 13) { Fence->Move(glm::vec3(-5.0f, 0.0f, 10.0f));  pos = glm::vec3(-5.0f*scaleFactor.x, 0.0f*scaleFactor.y, 10.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

			//house in the middle 
			if (i == 14) 
			{ Fence->Move(glm::vec3(2.0f, 0.0f, 0.5f));  pos = glm::vec3(2.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.5f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			if (i == 15)
			{
			Fence->Move(glm::vec3(1.0f, 0.0f, -7.5f));  pos = glm::vec3(1.0f*scaleFactor.x, 0.0f*scaleFactor.y, -7.5f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); 
			}
			if (i == 16)
			{
				Fence->Move(glm::vec3(1.0f, 0.0f, 17.0f));  pos = glm::vec3(1.0f*scaleFactor.x, 0.0f*scaleFactor.y, 17.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z);
			}
			if (i == 17)
			{
				Fence->Move(glm::vec3(8.0f, 0.0f, -7.5f));  pos = glm::vec3(8.0f*scaleFactor.x, 0.0f*scaleFactor.y, -7.5f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z);
			}
			if (i == 18)
			{
				Fence->Move(glm::vec3(8.0f, 0.0f, 17.0f));  pos = glm::vec3(8.0f*scaleFactor.x, 0.0f*scaleFactor.y, 17.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z);
			}
			if (i == 19)
			{
				Fence->Move(glm::vec3(47.0f, 0.0f, 3.0f));  pos = glm::vec3(47.0f*scaleFactor.x, 0.0f*scaleFactor.y, 3.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z);
			}

			gameObjects.push_back(Fence);

	}

	//first initialise a vector containing door information
	std::vector<glm::vec3> doors;
	doors.push_back(glm::vec3(45.0f, -12.5f, -26.0f));
	//doors.push_back(glm::vec3(37.5f, 0.0, 37.5f));
	//doors.push_back(glm::vec3(75.0f, 0.0, -25.0f));
	//doors.push_back(glm::vec3(75.0f, 0.0, 37.5f));
	//doors.push_back(glm::vec3(95.0f, 0.0, -6.25f));
	//doors.push_back(glm::vec3(95.0f, 0.0, 36.25f));

	//grid has to be the last game object added
	pathFindingGrid = new Grid(glm::vec2(500, 500), 5.0f, glm::vec3(0.0f, 0.0f, 0.0f), "boundingbox");
	pathFindingGrid->buildGrid(gameObjects, toonShader);
	pathFindingGrid->addEndPoints(doors);

	//initialise the path manager
	pathManager = new PathManager();
	pathManager->addGrid(pathFindingGrid);

	//set up the wavespawner
	waveSpawner = new WaveSpawner(pathFindingGrid);
	waveSpawner->setEndCoords(doors);
	waveSpawner->spawnWave(gameObjects, 0, toonShader, pathManager);

	testtxt = new Text(glm::vec2(5.0, 5.0), "assets/Fonts/ariali.ttf");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::update()
{
	std::cout << "c: " << mainCamera->getCameraPos().x << " " << mainCamera->getCameraPos().z << std::endl;


	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i] != nullptr) {
			gameObjects[i]->componentUpdate();
			gameObjects[i]->update();

			Enemy *e = dynamic_cast<Enemy*>(gameObjects[i]);
			if (e)
			{
				e->update();
			}
		}
	}
	if (Input::keyboard1.keys[GLFW_KEY_C]) {
		sassy->Move(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Input::keyboard1.keys[GLFW_KEY_V]) {
		sassy->Move(glm::vec3(-1.0f, 0.0f, 0.0f));
	}
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

	//update one path per frame so the computer doesnt melt
	if (pathManager->working == false) {
		pathManager->update(gameObjects, toonShader);
	}
	if (pathManager->working == true)
		pathManager->working = false;


	lezCamera.update();
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_ESCAPE]) SDL_SetRelativeMouseMode(SDL_FALSE); // TEMP
	else SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Game::draw()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glUniform1i(glGetUniformLocation(toonShader->getID(), "material.diffuse1"), diffuse);
	glUniform1i(glGetUniformLocation(toonShader->getID(), "material.specular1"), specular);
	glUniform1f(glGetUniformLocation(toonShader->getID(), "material.shininess"), shininess);
	glUniform3f(glGetUniformLocation(toonShader->getID(), "viewPos"), mainCamera->getCameraPos().x, mainCamera->getCameraPos().y, mainCamera->getCameraPos().z);
	//cout << glGetUniformLocation(toonShader->getID(), "viewPos") << endl;
	//cout << "viewpos; " << glGetUniformLocation(toonShader->getID(), "viewPos") << endl;
	//cout << "Diffuse; " << glGetUniformLocation(toonShader->getID(), "material.diffuse") << endl;
	//cout << "specular; " << glGetUniformLocation(toonShader->getID(), "material.specular") << endl;
	//cout << "shininess; " << glGetUniformLocation(toonShader->getID(), "material.shininess") << endl;
	glm::mat4 projection = (glm::perspective(float(glm::radians(60.0f)), 1280.0f / 720.0f, 1.0f, 150.0f));

	skybox->draw(projection * glm::mat4(glm::mat3(mainCamera->lookAtMat())));

	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i] != nullptr) {
			
			gameObjects[i]->componentDraw(mainCamera->lookAtMat());
		}
	}
	testtxt->draw("test", glm::vec3(1.0f, 1.0f, 1.0f));
}
