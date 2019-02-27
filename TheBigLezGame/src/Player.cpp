#include "Player.h"

Player::Player(Character character) : GameObject( character.fileLocation.c_str())
{

	selectCharacter = character;
}

Player::~Player()
{
}

void Player::update()
{
}
