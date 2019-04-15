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
	Image* background, *fog;
	float fogPos = 0;
	Image* logo;
	Button* singlePlayerBtn, *optionsBtn, *quitBtn;
	Text* testText;
	GLFWwindow* m_window;

	//timekeeping
	float current = 0.0f;
	float previous = 0.0f;

public:
	MainMenu();
	virtual ~MainMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};