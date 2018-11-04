#include "MainMenu.h"
#include <iostream>
#include <SDL.h>

MainMenu::MainMenu()
{

}

void MainMenu::handle(Menu * menu)
{
	std::cout << "Main Menu"
		<< "\n (1) Singleplayer "
		<< "\n (2) Options"
		<< "\n (3) Quit " << std::endl;

	selectedMenu = menu;
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
}
