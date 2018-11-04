#include "SinglePlayerMenu.h"
#include <iostream>
#include <SDL.h>

SinglePlayerMenu::SinglePlayerMenu()
{
}

void SinglePlayerMenu::handle(Menu * menu)
{
	singleplayerGame.init();
	selectedMenu = menu;
}

void SinglePlayerMenu::update()
{
	singleplayerGame.update();
}

void SinglePlayerMenu::draw()
{
	singleplayerGame.draw();
}
