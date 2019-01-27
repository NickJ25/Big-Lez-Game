#include "LobbyMenu.h"

LobbyMenu::LobbyMenu()
{

}

void LobbyMenu::handle(Menu * menu)
{
	background = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));
	
	m_window = glfwGetCurrentContext();
	backBtn = new Button(glm::vec2(640.0, 100.0), "Back");
	startBtn = new Button(glm::vec2(640.0, 340.0), "Start");

	selectedMenu = menu;
}

void LobbyMenu::update() 
{
	if (backBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getMainMenu());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	if (startBtn->buttonClick()) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		selectedMenu->setCurrent(selectedMenu->getSinglePlayer());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
}

void LobbyMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();
	backBtn->draw();
	startBtn->draw();
}