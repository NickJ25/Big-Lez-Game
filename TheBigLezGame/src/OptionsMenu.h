#pragma once
#include "MenuState.h"
#include "Menu.h"

class OptionsMenu : public MenuState {
public:
	OptionsMenu();
	virtual ~OptionsMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};