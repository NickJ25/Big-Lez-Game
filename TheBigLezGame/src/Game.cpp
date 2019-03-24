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

GameObject* sassy;

// Initalize Two Camera
//Camera lezCamera(glm::vec3(0.0f, 12.5f, 0.0f), FREECAM);

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

	environment->setShader(toonShader);
	environment->Move(glm::vec3(0.0f, 100.0f, 0.0f));
	gameObjects.push_back(environment);

	// Characters
	Player::Character BigLez;
	BigLez.fileLocation = "assets/Characters/BigLez/lez.dae";
	BigLez.name = "Leslie";
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


	sassy = new Player(ControllerComponent::CONTROLLER1, Sassy, glm::vec3(45.0f, -12.5f, 20.0f)); // Change to prop is issue?
	sassy->setShader(toonShader);
	//sassy->Move(glm::vec3(45.0f, -12.5f, 20.0f));
	sassy->setAnimation(5.0f, 1.0f);
	gameObjects.push_back(sassy);

	mainPlayer = new Player(ControllerComponent::KEYBOARD, BigLez, glm::vec3(0.0f, 0.0f, 0.0f));
	mainPlayer->setShader(toonShader);
	//mainPlayer->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	mainPlayer->Scale(glm::vec3(0.6f, 0.6f, 0.6f));
	//mainPlayer->setAnim(0);
	mainPlayer->setAnimation(5.0f, 1.0f);
	gameObjects.push_back(mainPlayer);

	GameObject* lezShotgun = new Gun("assets/Weapons/Shotgun/lezshotgun.dae", "Shotgun", 8, 8, false);
	lezShotgun->setShader(toonShader);
	lezShotgun->setAnimation(0.0f, 1.0f);
	mainPlayer->addWeapon(dynamic_cast<Weapon*> (lezShotgun));
	gameObjects.push_back(lezShotgun);

	GameObject* lezTest = new Prop("assets/Props/Table/Table.dae", glm::vec3(0.0f, 0.0f, 0.0f));
	lezTest->setShader(toonShader);
	lezTest->Rotate(-90.0f, glm::vec3(1.0, 0.0, 0.0));
	gameObjects.push_back(lezTest);

	// add environmental collision boxes for pathfinding an' such
	glm::vec3 fenceScaleVertical = glm::vec3(4.0f, 4.0f, 30.0f);
	glm::vec3 fenceScaleHorizontal = glm::vec3(30.0f, 4.0f, 4.0f);
	glm::vec3 test = glm::vec3(2.5, 2.5, 2.5);
	GameObject* Fence;


	for (int i = 0; i < 20; i++)
	{
		Fence = new Player(ControllerComponent::CONTROLLER1, cube, glm::vec3(0.0,0.0,0.0));
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
	std::vector<glm::vec3> bottomDoors, topDoors, leftDoors, rightDoors;
	leftDoors.push_back(glm::vec3(45.0f, -12.5f, -26.0f));
	topDoors.push_back(glm::vec3(37.5f, -12.5f, 37.5f));
	bottomDoors.push_back(glm::vec3(80.0f, -12.5f,  50.0f));
	rightDoors.push_back(glm::vec3(75.0f, -12.5f, -25.0f));
	//doors.push_back(glm::vec3(95.0f, 0.0, -6.25f));
	//doors.push_back(glm::vec3(95.0f, 0.0, 36.25f));

	//grid has to be the last game object added
	pathFindingGrid = new Grid(glm::vec2(500, 500), 5.0f, glm::vec3(0.0f, 0.0f, 0.0f), "boundingbox");
	pathFindingGrid->buildGrid(gameObjects, toonShader);
	//pathFindingGrid->addEndPoints(bottomDoors);

	//initialise the path manager
	pathManager = new PathManager();
	pathManager->addGrid(pathFindingGrid);

	//set up the wavespawner
	waveSpawner = new WaveSpawner(pathFindingGrid);
	waveSpawner->setEndCoords(bottomDoors, "Bottom");
	waveSpawner->setEndCoords(topDoors, "Top");
	waveSpawner->setEndCoords(leftDoors, "Left");
	waveSpawner->setEndCoords(rightDoors, "Right");
	waveSpawner->spawnWave(gameObjects, 0, toonShader, pathManager);

	resumeBtn = new Button(Button::NORMAL, glm::vec2(640.0, 460.0), "Resume");
	mainMenuBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Quit");
	pauseBackground = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));

	testtxt = new Text(glm::vec2(590.0, 445.0), "assets/Fonts/Another_.ttf");
	testtxt2 = new Text(glm::vec2(600.0, 325.0), "assets/Fonts/Another_.ttf");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Game::update()
{
	if(isGameRunning == true)
	{
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
		//lezCamera.update();
		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_ESCAPE]) SDL_SetRelativeMouseMode(SDL_FALSE); // TEMP
		else SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	
	if (Input::keyboard1.keys[GLFW_KEY_P])
	{
		isGameRunning = false;	
		g_window = glfwGetCurrentContext();
		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

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

	if (Input::controller1.buttons[0]) {
		cout << "A" << endl;
	}
	if (Input::controller1.buttons[1]) {
		cout << "B" << endl;
	}
	if (Input::controller1.buttons[2]) {
		cout << "X" << endl;
	}
	if (Input::controller1.buttons[3]) {
		cout << "Y" << endl;
	}
	if (Input::controller1.buttons[4]) {
		cout << "Left Bumper" << endl;
	}
	if (Input::controller1.buttons[5]) {
		cout << "Right Bumper" << endl;
	}
	if (Input::controller1.buttons[6]) {
		cout << "Back" << endl;
	}
	if (Input::controller1.buttons[7]) {
		cout << "Start" << endl;
	}
	if (Input::controller1.buttons[8]) {
		cout << "Left Thumb" << endl;
	}
	if (Input::controller1.buttons[9]) {
		cout << "Right Thumb" << endl;
	}
	if (Input::controller1.buttons[10]) {
		cout << "DPad UP" << endl;
	}
	if (Input::controller1.buttons[11]) {
		cout << "DPad RIGHT" << endl;
	}
	if (Input::controller1.buttons[12]) {
		cout << "DPad DOWN" << endl;
	}
	if (Input::controller1.buttons[13]) {
		cout << "DPad LEFT" << endl;
	}
	if (Input::controller1.buttons[14]) {
		cout << "Guide" << endl;
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

	//update one path per frame so the computer doesnt melt
	if (pathManager->working == false) {
		pathManager->update(gameObjects, toonShader);
	}
	if (pathManager->working == true)
		pathManager->working = false;

	//cout << "cpos: " << lezCamera.getCameraPos().x << " " << lezCamera.getCameraPos().z << endl;
	//lezCamera.update();/// ----------------------------------------------------------------------CHECK
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

	//glUniform3f(glGetUniformLocation(toonShader->getID(), "viewPos"), lezCamera.getCameraPos().x, lezCamera.getCameraPos().y, lezCamera.getCameraPos().z);
	glUniform3f(glGetUniformLocation(toonShader->getID(), "viewPos"), mainPlayer->getCamera()->getCameraPos().x, mainPlayer->getCamera()->getCameraPos().y, mainPlayer->getCamera()->getCameraPos().z);

	glm::mat4 projection = (glm::perspective(float(glm::radians(60.0f)), 1280.0f / 720.0f, 1.0f, 150.0f));

	skybox->draw(projection * glm::mat4(glm::mat3(mainPlayer->getCamera()->lookAtMat())));

	//skybox->draw(projection * glm::mat4(glm::mat3(lezCamera.lookAtMat())));

	if (isGameRunning == false)
	{
		// Draws pause menu
		resumeBtn->draw();
		mainMenuBtn->draw(); 
		testtxt->draw("Resume", glm::vec3(1.0f, 1.0f, 1.0f));
		testtxt2->draw("Quit", glm::vec3(1.0f, 1.0f, 1.0f));
		pauseBackground->draw();
	}

	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i] != nullptr) {
			gameObjects[i]->componentDraw(mainPlayer->getCamera()->lookAtMat());
			//gameObjects[i]->componentDraw(lezCamera.lookAtMat());
		}
	}
	
}
