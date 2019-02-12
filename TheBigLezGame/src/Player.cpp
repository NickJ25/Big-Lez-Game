#include "Player.h"

Player::Player(Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{

	
}

Player::~Player()
{
}

void Player::update()
{
}
