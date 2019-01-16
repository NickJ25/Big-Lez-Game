#pragma once
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
	Button* buttonTest;
	Text* testText;

	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
	
public:
	MainMenu();
	virtual ~MainMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();

	static windowGLFW* mainWindow;
};