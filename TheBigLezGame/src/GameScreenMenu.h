#pragma once
#include "MenuState.h"
#include "Menu.h"
#include "Game.h"
#include "Player.h"
#include <vector>

class GameScreenMenu : public MenuState {
private:
	Game* m_mainGame = nullptr;
	vector< Player::Character*> m_players;
public:
	GameScreenMenu();
	virtual ~GameScreenMenu();
	void handle(Menu* menu);
	void update();
	void draw();
	void addPlayers(vector<Player::Character*> &players);
};