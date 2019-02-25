#include "ControlsMenu.h"
#include <iostream>
#include <SDL.h>

ControlsMenu::ControlsMenu()
{
}

void ControlsMenu::handle(Menu * menu)
{
	std::cout << "Options"
		<< "\n (1) Back "<< std::endl;
	selectedMenu = menu;
}

void ControlsMenu::update()
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_1] && keys[SDL_KEYUP]) {
		selectedMenu->setCurrent(selectedMenu->getOptions());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
}

void ControlsMenu::draw()
{

}
