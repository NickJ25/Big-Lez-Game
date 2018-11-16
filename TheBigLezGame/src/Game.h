#pragma once
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <vector>
#include <iostream>

#include "Camera.h"

using namespace std;

class Game {
private:
	Camera* mainCamera;

public:
	Game() {};
	~Game() {};
	void init();
	void update();
	void draw();
};
