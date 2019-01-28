#include "GraphicsMenu.h"

GraphicsMenu::GraphicsMenu()
{
}

void GraphicsMenu::handle(Menu * menu)
{
	background = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));
	selectedMenu = menu;
	backBtn = new Button(glm::vec2(640.0, 100.0), "Back");
}

void GraphicsMenu::update()
{
	if (backBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getOptions());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
}

void GraphicsMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();
	backBtn->draw();
}
