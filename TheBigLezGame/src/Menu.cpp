#include "Menu.h"
#include "MainMenu.h"
#include "SinglePlayerMenu.h"
#include "OptionsMenu.h"
#include "ControlsMenu.h"
#include "GraphicsMenu.h"
#include "AudioMenu.h"
#include "ScoreboardMenu.h"
#include "LobbyMenu.h"


Menu::Menu()
{
	mainMenu = new MainMenu();
	gameScreen = new SinglePlayerMenu();
	options = new OptionsMenu();
	controls = new ControlsMenu();
	graphics = new GraphicsMenu();
	audio = new AudioMenu();
	scoreboard = new ScoreboardMenu();
	lobby = new LobbyMenu();
	current = mainMenu;
	current->handle(this);

	AmbientEngine->play2D("Assets/Sounds/Ambient/MenuMusic.wav", true);
}

void Menu::setCurrent(MenuState * menu)
{
	current = menu;
}

MenuState * Menu::getCurrentState()
{
	return current;
}

void Menu::updateMenus()
{
	if (current == gameScreen)
		AmbientEngine->stopAllSounds();
	current->update();
}

void Menu::drawMenus()
{
	current->draw();
}

MenuState * Menu::getMainMenu()
{
	return mainMenu;
}

MenuState * Menu::getGameScreen()
{
	return gameScreen;
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

MenuState * Menu::getLobby()
{
	return lobby;
}
