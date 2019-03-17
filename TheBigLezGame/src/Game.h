#pragma once
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <vector>
#include <iostream>

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
#include "WaveSpawner.h"
#include "Grid.h"
#include "PathManager.h"

using namespace std;

class Game {
private:
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
public:
	Game() {};
	~Game() {};
	void init();
	void update();
	void draw();
	bool checkCollision(GameObject* a, GameObject* b);

	//for calculating contact normal
	const glm::vec3 nup = glm::vec3(0, 1, 0);
	const glm::vec3 ndown = glm::vec3(0, -1, 0);
	const glm::vec3 nright = glm::vec3(1, 0, 0);
	const glm::vec3 nleft = glm::vec3(-1, 0, 0);

	char computePointMask(glm::vec3 p, Enemy* e);
	glm::vec3 getFaceNormal(glm::vec3 p, Enemy* e);
	bool pointIsAbovePlane(const glm::vec3 & P, const glm::vec3 & n, float d);

	glm::vec3 contactNormal;
};
