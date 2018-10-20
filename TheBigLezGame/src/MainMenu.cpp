#include "MainMenu.h"
#include <iostream>
#include <SDL.h>

MainMenu::MainMenu()
{

}

void MainMenu::handle(Menu * menu)
{
	std::cout << "Main Menu" << std::endl;
	selectedMenu = menu;
}

void MainMenu::update()
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_1]) {
		selectedMenu->setCurrent(selectedMenu->getControls());
		selectedMenu->getCurrentState()->handle(selectedMenu);
		
	}
	std::cout << "Main Menu" << std::endl;
	
}

void MainMenu::draw()
{
}
