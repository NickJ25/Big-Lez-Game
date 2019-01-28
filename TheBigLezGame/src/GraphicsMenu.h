#pragma once
#include "MenuState.h"
#include "Menu.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"
#include "windowGLFW.h"

class GraphicsMenu : public MenuState {
private:
	Image* background;
	Button* backBtn;
public:
	GraphicsMenu();
	virtual ~GraphicsMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};