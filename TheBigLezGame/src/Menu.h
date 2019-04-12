#pragma once
#include "MenuState.h"

#include <irrKlang.h>

class Menu {
private:
	MenuState* current;
	MenuState* mainMenu;
	MenuState* singlePlayer;
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
		delete singlePlayer;
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
	MenuState* getSinglePlayer();
	MenuState* getOptions();
	MenuState* getControls();
	MenuState* getGraphics();
	MenuState* getScoreboard();
	MenuState* getLobby();
};