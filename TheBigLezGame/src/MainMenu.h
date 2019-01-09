#pragma once
#include "MenuState.h"
#include "Menu.h"
#include "Button.h"
#include "Image.h"

class MainMenu : public MenuState {
private:
	Image* background;
	Button* buttonTest;
public:
	MainMenu();
	virtual ~MainMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};