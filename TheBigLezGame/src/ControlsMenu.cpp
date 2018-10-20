#include "ControlsMenu.h"
#include <iostream>
#include <SDL.h>

ControlsMenu::ControlsMenu()
{
}

void ControlsMenu::handle(Menu * menu)
{
	selectedMenu = menu;
}

void ControlsMenu::update()
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_2]) {
		selectedMenu->setCurrent(selectedMenu->getMainMenu());
		selectedMenu->getCurrentState()->handle(selectedMenu);

	}
	std::cout << "Controls Menu" << std::endl;
}

void ControlsMenu::draw()
{
}
