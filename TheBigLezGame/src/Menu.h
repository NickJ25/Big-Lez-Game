#pragma once
#include "MenuState.h"

class Menu {
private:
	MenuState* current;
	MenuState* mainMenu;
	MenuState* singlePlayer;
	MenuState* options;
	MenuState* controls;
	MenuState* graphics;
	MenuState* audio;
	MenuState* scoreboard;
public:
	Menu();
	virtual ~Menu()
	{
		delete mainMenu;
		delete singlePlayer;
		delete options;
		delete controls;
		delete graphics;
		delete audio;
		delete scoreboard;
		//delete current;
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
	MenuState* getAudio();
	MenuState* getScoreboard();
};