#include "Menu.h"
#include "MainMenu.h"
#include "SinglePlayerMenu.h"
#include "OptionsMenu.h"
#include "ControlsMenu.h"
#include "GraphicsMenu.h"
#include "AudioMenu.h"
#include "ScoreboardMenu.h"


Menu::Menu()
{
	mainMenu = new MainMenu();
	singlePlayer = new SinglePlayerMenu();
	options = new OptionsMenu();
	controls = new ControlsMenu();
	graphics = new GraphicsMenu();
	audio = new AudioMenu();
	scoreboard = new ScoreboardMenu();
	current = mainMenu;
	current->handle(this);
}

void Menu::setCurrent(MenuState * menu)
{
	current = menu;
}

void Menu::updateMenus()
{
	current->update();
}

void Menu::drawMenus()
{

}

MenuState * Menu::getCurrentState()
{
	return current;
}

MenuState * Menu::getMainMenu()
{
	return mainMenu;
}

MenuState * Menu::getSinglePlayer()
{
	return singlePlayer;
}

MenuState * Menu::getOptions()
{
	return options;
}

MenuState * Menu::getControls()
{
	return controls;
}

MenuState * Menu::getGraphics()
{
	return graphics;
}

MenuState * Menu::getAudio()
{
	return audio;
}

MenuState * Menu::getScoreboard()
{
	return scoreboard;
}
