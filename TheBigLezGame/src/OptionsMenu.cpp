#include "OptionsMenu.h"
#include <iostream>
#include <SDL.h>


OptionsMenu::OptionsMenu()
{

}

void OptionsMenu::handle(Menu * menu)
{
	std::cout << "Options"
		<< "\n (1) Audio "
		<< "\n (2) Controls"
		<< "\n (3) Graphics "
		<< "\n (4) Back " << std::endl;
	selectedMenu = menu;
}

void OptionsMenu::update()
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_1]) {
		selectedMenu->setCurrent(selectedMenu->getSinglePlayer());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
	if (keys[SDL_SCANCODE_2]) {
		selectedMenu->setCurrent(selectedMenu->getControls());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
	if (keys[SDL_SCANCODE_3]) {
		selectedMenu->setCurrent(selectedMenu->getGraphics());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
	if (keys[SDL_SCANCODE_3]) {
		selectedMenu->setCurrent(selectedMenu->getMainMenu());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
	std::cout << "Options Update" << std::endl;
}

void OptionsMenu::draw()
{
	std::cout << "Options Draw" << std::endl;
}
