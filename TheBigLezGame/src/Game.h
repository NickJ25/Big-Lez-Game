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
#include "Text.h"
#include "Grid.h"
#include "PathManager.h"
#include "ControllerComponent.h"

using namespace std;

class Game {
private:
	Player* ALL_PLAYERS[2]; // Hold all players in this array?

	Player* mainPlayer;
	Text* testtxt;
	bool isGameRunning = true; 
	Button* resumeBtn, *mainMenuBtn;
	GLFWwindow* g_window;
	Menu* selectedMenu;
	Image* pauseBackground;
	Text* testtxt2;
	bool showBoundingBoxes;

public:
	Game() {};
	~Game() {};
	void init();
	void update();
	void draw();
};
