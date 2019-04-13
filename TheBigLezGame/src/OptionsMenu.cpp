#include "OptionsMenu.h"
#include <iostream>

OptionsMenu::OptionsMenu()
{

}

void OptionsMenu::handle(Menu * menu)
{
	background = new Image("assets/Art/background.png", glm::vec2(640.0, 360.0));
	fog = new Image("assets/Art/fog.png", glm::vec2(640.0f, 0.0f));

	selectedMenu = menu;
	backBtn = new Button(Button::NORMAL, glm::vec2(640.0, 100.0), "Back");
	graphicsBtn = new Button(Button::NORMAL, glm::vec2(640.0, 580.0), "Graphics");
	controlsBtn = new Button(Button::NORMAL, glm::vec2(640.0, 460.0), "Controls");
	audioBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Audio");
}

void OptionsMenu::update()
{
	// Fog Scrolling
	fog->translate(glm::vec2(fogPos, 360));
	fog->scale(glm::vec2(3840.0f, 1080.0f), true);
	std::cout << fogPos << "\n";
	fogPos += 4;
	if (fogPos > 3800) fogPos = 0;

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

}

void OptionsMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();
	fog->draw();
	backBtn->draw();
	graphicsBtn->draw();
	controlsBtn->draw();
	audioBtn->draw();
}
