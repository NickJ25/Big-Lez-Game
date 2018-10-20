#pragma once
#include "MenuState.h"
#include "Menu.h"

class SinglePlayerMenu : public MenuState {
public:
	SinglePlayerMenu();
	virtual ~SinglePlayerMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};