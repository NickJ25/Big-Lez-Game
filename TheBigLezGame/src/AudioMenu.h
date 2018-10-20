#pragma once
#include "MenuState.h"
#include "Menu.h"

class AudioMenu : public MenuState {
public:
	AudioMenu();
	virtual ~AudioMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};