#include "Game.h"

vector<GameObject*> gameObjects;
Skybox* skybox;
Shader *toonShader;
WaveSpawner* waveSpawner;

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


	GameObject* environment = new Prop("assets/Props/Map/envMap.dae", glm::vec3(0.0f, 0.0f, 0.0f));
	environment->setShader(toonShader);
	gameObjects.push_back(environment);

	GameObject* roof = new Prop("assets/Props/Map/roof.dae", glm::vec3(0.0f, 0.0f, 0.0f));
	roof->setShader(toonShader);
	gameObjects.push_back(roof);

	// Characters
	Player::Character BigLez;
	BigLez.fileLocation = "assets/Characters/BigLez/lez.dae";
	BigLez.name = "Leslie";

	Player::Character Sassy;
	Sassy.fileLocation = "assets/Characters/Sassy/sassy.dae";
	Sassy.name = "Sassy";

	waveSpawner = new WaveSpawner(150, glm::vec3(0, 0, 0));
	waveSpawner->spawnWave(gameObjects, 0, toonShader);

	cout << "first check: " << gameObjects.size() << endl;

	GameObject* bigLez = new Player(BigLez, glm::vec3(0.0f, -12.5f, 50.0f));
	bigLez->setShader(toonShader);
	bigLez->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	bigLez->Scale(glm::vec3(0.6f, 0.6f, 0.6f));
	bigLez->setAnim(0);
	gameObjects.push_back(bigLez);

	GameObject* sassy = new Player(Sassy, glm::vec3(150.0f, -12.5f, 50.0f));
	sassy->setShader(toonShader);
	sassy->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	sassy->Scale(glm::vec3(0.6f, 0.6f, 0.6f));
	sassy->setAnim(0);
	gameObjects.push_back(sassy);
	
	cout << "second check" << gameObjects.size() << endl;

	GameObject* lezTest = new Prop("assets/Props/Table/Table.dae", glm::vec3(0.0f, 0.0f, 0.0f));
	lezTest->setShader(toonShader);
	lezTest->Rotate(-90.0f, glm::vec3(1.0, 0.0, 0.0));
	gameObjects.push_back(lezTest);

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
