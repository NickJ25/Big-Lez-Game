#pragma once
#include "MenuState.h"

#include <irrKlang.h>

class Menu {
private:
	MenuState* current;
	MenuState* mainMenu;
	MenuState* gameScreen;
	MenuState* options;
	MenuState* controls;
	MenuState* graphics;
	MenuState* scoreboard;
	MenuState* lobby;

	//background music engine
	irrklang::ISoundEngine *AmbientEngine = irrklang::createIrrKlangDevice();
public:
	Menu();
	virtual ~Menu()
	{
		delete mainMenu;
		delete gameScreen;
		delete options;
		delete controls;
		delete graphics;
		delete scoreboard;
	}
	void setCurrent(MenuState* menu);
	void updateMenus();
	void drawMenus();
	MenuState* getCurrentState();
	MenuState* getMainMenu();
	MenuState* getGameScreen();
	MenuState* getOptions();
	MenuState* getControls();
	MenuState* getGraphics();
	MenuState* getScoreboard();
	MenuState* getLobby();
};