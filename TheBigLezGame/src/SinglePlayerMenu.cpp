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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(singleplayerGame)
	singleplayerGame->update();
}

void SinglePlayerMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (singleplayerGame)
	singleplayerGame->draw();
}


