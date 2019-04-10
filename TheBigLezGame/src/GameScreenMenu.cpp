#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu()
{
}

GameScreenMenu::~GameScreenMenu()
{
}

void GameScreenMenu::handle(Menu * menu)
{
	m_mainGame = new Game();
	selectedMenu = menu;
}

void GameScreenMenu::update()
{
	if(m_mainGame) m_mainGame->update();
}

void GameScreenMenu::draw()
{
	if (m_mainGame) m_mainGame->draw();
}

void GameScreenMenu::addPlayers(vector<Player::Character*> &players)
{
	m_players = players;
}

