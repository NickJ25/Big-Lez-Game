#include "SinglePlayerMenu.h"
#include <iostream>

SinglePlayerMenu::SinglePlayerMenu()
{
}

void SinglePlayerMenu::handle(Menu * menu)
{
	singleplayerGame = new Game;
	selectedMenu = menu;
}

void SinglePlayerMenu::update()
{
	if(singleplayerGame)
	singleplayerGame->update();
}

void SinglePlayerMenu::draw()
{
	if (singleplayerGame)
	singleplayerGame->draw();
}


