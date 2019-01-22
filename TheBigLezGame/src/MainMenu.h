#pragma once
#include <iostream>
#include "MenuState.h"
#include "Menu.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"
#include "windowGLFW.h"
#include "GLFW/glfw3.h"

class MainMenu : public MenuState {
private:
	Image* background;
	Image* logo;
	Button* singlePlayerBtn, *optionsBtn, *quitBtn;
	Text* testText;
public:
	MainMenu();
	virtual ~MainMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};