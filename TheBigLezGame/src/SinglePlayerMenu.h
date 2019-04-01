#pragma once
#include "MenuState.h"
#include "Menu.h"
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include "Game.h"
#include "Button.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <vector>

using namespace std;

class SinglePlayerMenu : public MenuState {
private:
	Game *singleplayerGame;
public:
	SinglePlayerMenu();
	virtual ~SinglePlayerMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
	
};