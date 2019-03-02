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
#include "WaveSpawner.h"

#include "Text.h"
#include "WaveSpawner.h"
#include "Grid.h"
#include "PathManager.h"

using namespace std;

class Game {
private:
	Camera* mainCamera;
	Text* testtxt;

	bool showBoundingBoxes;

public:
	Game() {};
	~Game() {};
	void init();
	void update();
	void draw();
};
