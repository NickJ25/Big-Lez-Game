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
	gameRunning == true; 
}

void SinglePlayerMenu::draw()
{
	singleplayerGame.draw();
}

void SinglePlayerMenu::pause()
{
	if (gameRunning == true)
	{
		singleplayerGame.update;
	}
	else {
			
		}
}