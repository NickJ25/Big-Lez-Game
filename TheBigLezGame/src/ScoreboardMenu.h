#pragma once
#include "MenuState.h"
#include "Menu.h"

class ScoreboardMenu : public MenuState {
public:
	ScoreboardMenu();
	virtual ~ScoreboardMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};