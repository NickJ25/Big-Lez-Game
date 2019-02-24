#include "Game.h"

vector<GameObject*> gameObjects;
Skybox* skybox;
Shader *toonShader;
WaveSpawner* waveSpawner;
Grid* pathFindingGrid;

// Initalize Two Camera
Camera lezCamera(glm::vec3(0.0f, 4.0f, 6.0f), DYNAMIC);

//rt3d::lightStruct light0 = {
//	{1.0f, 1.0f, 1.0f, 1.0f}, // ambient
//	{1.0f, 1.0f, 1.0f, 1.0f}, // diffuse
//	{1.0f, 1.0f, 1.0f, 1.0f}, // specular
//	{-10.0f, 10.0f, 10.0f, 1.0f}  // position
//};
//glm::vec4 lightPos(-7.0f, 3.6f, -7.5f, 1.0f); //light position

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

	////	Init Objects	////
	GameObject* dirLight = new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.9f, 0.9f, 0.9f));
	dirLight->setShader(toonShader);
	gameObjects.push_back(dirLight);


	GameObject* environment = new Prop("assets/Props/Map/envMap.dae", glm::vec3(0.0f, 100.0f, 0.0f));
	environment->setShader(toonShader);
	environment->Move(glm::vec3(0.0f, 100.0f, 0.0f));
	gameObjects.push_back(environment);

	//GameObject* roof = new Prop("assets/Props/Map/roof.dae", glm::vec3(0.0f, 0.0f, 0.0f));
	//roof->setShader(toonShader);
	//gameObjects.push_back(roof);

	// Characters
	Player::Character BigLez;
	BigLez.fileLocation = "assets/Characters/BigLez/lez.dae";
	BigLez.name = "Leslie";

	Player::Character Sassy;
	Sassy.fileLocation = "assets/Props/Map/gridblock.dae";
	Sassy.name = "Sassy";

	Player::Character cube;
	cube.fileLocation = "assets/Props/Map/gridblock.dae";
	cube.name = "anything";

	//waveSpawner = new WaveSpawner(150, glm::vec3(0, -12.5, 50));
	//waveSpawner->spawnWave(gameObjects, 0, toonShader);

	//GameObject* bigLez = new Player(BigLez, glm::vec3(20.0f, -10.5f, 0.0f));
	//bigLez->setShader(toonShader);
	//bigLez->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	////bigLez->Scale(glm::vec3(0.6f, 0.6f, 0.6f));
	//bigLez->setAnim(0);
	//bigLez->addCollision(glm::vec3(20.0f, -10.5f, 0.0f), 1.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	//gameObjects.push_back(bigLez);


	//GameObject* sassy = new Player(Sassy, glm::vec3(150.0f, -12.5f, 50.0f));
	//sassy->setShader(toonShader);
	//sassy->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//sassy->Scale(glm::vec3(0.6f, 0.6f, 0.6f));
	//sassy->setAnim(0);
	//gameObjects.push_back(sassy);


	// add environmental collision boxes for pathfinding an' such
	glm::vec3 fenceScaleVertical = glm::vec3(4.0f, 4.0f, 30.0f);
	glm::vec3 fenceScaleHorizontal = glm::vec3(30.0f, 4.0f, 4.0f);
	glm::vec3 test = glm::vec3(2.5, 2.5, 2.5);
	GameObject* Fence;

	for (int i = 0; i < 14; i++)
	{
		Fence = new Player(cube);
		Fence->setShader(toonShader);
		Fence->setAnim(0);

		glm::vec3 scaleFactor = fenceScaleVertical;
		if (i >= 4) scaleFactor = fenceScaleHorizontal;
		
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

			//front and back windows
			//if (i == 14) { scaleFactor = test; Fence->Move(glm::vec3(15.0f, 0.0f, -10.0f));  pos = glm::vec3(15.0f*scaleFactor.x, 0.0f*scaleFactor.y, -10.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			//if (i == 15) { scaleFactor = test; Fence->Move(glm::vec3(15.0f, 0.0f, 15.0f));  pos = glm::vec3(15.0f*scaleFactor.x, 0.0f*scaleFactor.y, 15.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			//if (i == 16) { scaleFactor = test; Fence->Move(glm::vec3(30.0f, 0.0f, -10.0f));  pos = glm::vec3(30.0f*scaleFactor.x, 0.0f*scaleFactor.y, -10.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			//if (i == 17) { scaleFactor = test; Fence->Move(glm::vec3(30.0f, 0.0f, 15.0f));  pos = glm::vec3(30.0f*scaleFactor.x, 0.0f*scaleFactor.y, 15.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

			////side windows
			//if (i == 18) { scaleFactor = test; Fence->Move(glm::vec3(38.0f, 0.0f, -2.5f));  pos = glm::vec3(38.0f*scaleFactor.x, 0.0f*scaleFactor.y, -2.5f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }
			//if (i == 19) { scaleFactor = test; Fence->Move(glm::vec3(38.0f, 0.0f, 14.5f));  pos = glm::vec3(38.0f*scaleFactor.x, 0.0f*scaleFactor.y, 14.5f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); }

		//gameObjects.push_back(Fence);

	}

	waveSpawner = new WaveSpawner();
	waveSpawner->spawnWave(gameObjects, 0, toonShader);

	//grid has to be added last
	pathFindingGrid = new Grid(glm::vec2(500, 500), 10.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	pathFindingGrid->buildGrid(gameObjects, toonShader);

	testtxt = new Text(glm::vec2(5.0, 5.0), "assets/Fonts/ariali.ttf");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::update()
{


	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i] != nullptr) {
			gameObjects[i]->componentUpdate();
			gameObjects[i]->update();

		}
	}

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
