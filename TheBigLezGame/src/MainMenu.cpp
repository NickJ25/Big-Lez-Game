#include "MainMenu.h"

MainMenu::MainMenu()
{

}

void MainMenu::handle(Menu * menu)
{
	background = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));
	logo = new Image("assets/Art/bigLezLogo.png", glm::vec2(640.0, 560.0));
	logo->scale(glm::vec2(0.5, 0.4));
	singlePlayerBtn = new Button(glm::vec2(640.0, 340.0), "Singleplayer");
	optionsBtn = new Button(glm::vec2(640.0, 220.0), "Options");
	quitBtn = new Button(glm::vec2(640.0, 100.0), "Quit");
	testText = new Text(glm::vec2(5.0, 5.0), "assets/Fonts/ariali.ttf");
	testText->scale(glm::vec2(0.5, 0.5));

	selectedMenu = menu;
}

void MainMenu::update()
{
	if (singlePlayerBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getSinglePlayer());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	if (optionsBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getOptions());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	if (quitBtn->buttonClick()) {

	}
}

void MainMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();
	logo->draw();
	singlePlayerBtn->draw();
	optionsBtn->draw();
	quitBtn->draw();
	testText->draw("Developed by Group 3", glm::vec3(1.0,1.0,1.0));
}
