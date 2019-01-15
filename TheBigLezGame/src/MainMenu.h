#pragma once
#include "MenuState.h"
#include "Menu.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"

#include "GLFW/glfw3.h"

class MainMenu : public MenuState {
private:
	Image* background;
	Button* buttonTest;
	Text* testText;
public:
	MainMenu();
	virtual ~MainMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};