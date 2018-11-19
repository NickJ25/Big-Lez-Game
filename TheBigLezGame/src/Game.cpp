#include "Game.h"

vector<GameObject*> gameObjects;
Shader *toonShader;

// Initalize Two Camera
Camera lezCamera(glm::vec3(0.0f, 4.0f, 6.0f), DYNAMIC);
//Camera debugCamera();

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

	GameObject* dirLight = new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.9f, 0.9f, 0.9f));
	dirLight->setShader(toonShader);
	gameObjects.push_back(dirLight);
	GameObject* spotLight = new SpotLight(mainCamera->getCameraPos(), mainCamera->getCameraFront(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.1f), 0.4, 3);
	spotLight->setShader(toonShader);
	gameObjects.push_back(spotLight);
	GameObject* pointLight = new PointLight(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.09f, 0.05f, 0.09f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.32f));
	pointLight->setShader(toonShader);
	gameObjects.push_back(pointLight);
	
	GameObject* table = new Prop("assets/Props/Table/table.obj", glm::vec3(0.0f, 0.0f, 0.0f));
	table->setShader(toonShader);
	table->Rotate(90, glm::vec3(1, 1, 1));
	//table->Move(glm::vec3(10.0f, 0.0f, 0.0f));
	gameObjects.push_back(table);
	

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

	glUniform1i(glGetUniformLocation(toonShader->getID(), "material.diffuse"), diffuse);
	cout << "Diffuse; " << glGetUniformLocation(toonShader->getID(), "material.diffuse") << endl;
	glUniform1i(glGetUniformLocation(toonShader->getID(), "material.specular"), specular);
	cout << "specular; " << glGetUniformLocation(toonShader->getID(), "material.specular") << endl;
	glUniform1f(glGetUniformLocation(toonShader->getID(), "material.shininess"), shininess);
	cout << "shininess; " << glGetUniformLocation(toonShader->getID(), "material.shininess") << endl;
	glUniform3f(glGetUniformLocation(toonShader->getID(), "viewPos"), mainCamera->getCameraPos().x, mainCamera->getCameraPos().y, mainCamera->getCameraPos().z);
	cout << "viewpos; " << glGetUniformLocation(toonShader->getID(), "viewPos") << endl;

	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i] != nullptr) {
			gameObjects[i]->componentDraw(mainCamera->lookAtMat());
		}
	}
}
