#pragma once
#include "MenuState.h"
#include "Menu.h"

class MainMenu : public MenuState {
public:
	MainMenu();
	virtual ~MainMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};