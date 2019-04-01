#include "SinglePlayerMenu.h"
#include <iostream>
#include <SDL.h>

SinglePlayerMenu::SinglePlayerMenu()
{
}

void SinglePlayerMenu::handle(Menu * menu)
{
	singleplayerGame = new Game;
	//singleplayerGame->init();
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


