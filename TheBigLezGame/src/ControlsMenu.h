#pragma once
#include "MenuState.h"
#include "Menu.h"

class ControlsMenu : public MenuState {
public:
	ControlsMenu();
	virtual ~ControlsMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};