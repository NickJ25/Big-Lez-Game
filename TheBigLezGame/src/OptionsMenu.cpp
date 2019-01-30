#include "OptionsMenu.h"
#include <iostream>
#include <SDL.h>


OptionsMenu::OptionsMenu()
{

}

void OptionsMenu::handle(Menu * menu)
{
	background = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));
	selectedMenu = menu;
	backBtn = new Button(Button::NORMAL, glm::vec2(640.0, 100.0), "Back");
	graphicsBtn = new Button(Button::NORMAL, glm::vec2(640.0, 580.0), "Graphics");
	controlsBtn = new Button(Button::NORMAL, glm::vec2(640.0, 460.0), "Controls");
	audioBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Audio");
}

void OptionsMenu::update()
{
	if (backBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getMainMenu());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	if (graphicsBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getGraphics());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	if (controlsBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getControls());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	if (audioBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getAudio());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
}

void OptionsMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();
	backBtn->draw();
	graphicsBtn->draw();
	controlsBtn->draw();
	audioBtn->draw();
}
