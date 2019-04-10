#pragma once
#include "MenuState.h"
#include "Menu.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"
#include "windowGLFW.h"

class OptionsMenu : public MenuState {
private:
	Image* background, *fog;
	float fogPos = 0;

	Button* backBtn, *graphicsBtn, *controlsBtn, *audioBtn;
public:
	OptionsMenu();
	virtual ~OptionsMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};