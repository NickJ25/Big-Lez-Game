#pragma once
#include "MenuState.h"
#include "Menu.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"
#include "windowGLFW.h"

//std library
#include <string>

class GraphicsMenu : public MenuState {
private:
	Image* background;
	Text* resolutionTxt;
	Button* backBtn, *resolutionBtn, *antiAlisBtn, *applyBtn;
	Button* leftResoBtn, *rightResoBtn;
	Button* leftAABtn, *rightAABtn;
	GLFWwindow* m_window;

	// Resolution button
	int newWidth, newHeight;
	int resoMode, aaMode;
public:
	GraphicsMenu();
	virtual ~GraphicsMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};