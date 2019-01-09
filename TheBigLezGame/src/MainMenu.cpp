#include "MainMenu.h"
#include <iostream>
#include <SDL.h>
#include "Image.h"

MainMenu::MainMenu()
{

}

void MainMenu::handle(Menu * menu)
{
	std::cout << "Main Menu"
		<< "\n (1) Singleplayer "
		<< "\n (2) Options"
		<< "\n (3) Quit " << std::endl;
	background = new Image("assets/Art/tempBackground.png");
	//buttonTest = new Button(glm::vec2(0.0, 0.0), "djdj");
	selectedMenu = menu;
	//selectedMenu->setCurrent(selectedMenu->getSinglePlayer());
	//selectedMenu->getCurrentState()->handle(selectedMenu);
}

void MainMenu::update()
{
		
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_1]) {
		selectedMenu->setCurrent(selectedMenu->getSinglePlayer());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
	if (keys[SDL_SCANCODE_2]) {
		selectedMenu->setCurrent(selectedMenu->getOptions());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
	if (keys[SDL_SCANCODE_3]) {
		SDL_Quit();
		exit(0);
	}
}

void MainMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();
	//buttonTest->draw();
}
