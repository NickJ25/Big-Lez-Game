#pragma once
#include "MenuState.h"
#include "Menu.h"

class GraphicsMenu : public MenuState {
public:
	GraphicsMenu();
	virtual ~GraphicsMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};