#pragma once
#include "MenuState.h"
#include "Menu.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"
#include "windowGLFW.h"

class LobbyMenu : public MenuState {
private:
	Image* background;
	Button* backBtn, *startBtn;
	GLFWwindow* m_window;
public:
	LobbyMenu();
	virtual ~LobbyMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};