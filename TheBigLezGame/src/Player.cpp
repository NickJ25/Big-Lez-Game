#include "Player.h"

Player::Player(Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	m_playerCamera = new Camera(startPos, DYNAMIC);
	
}

Player::~Player()
{
	delete m_playerCamera;
}

void Player::playAnimation()
{

}

Camera* Player::getCamera()
{
	return m_playerCamera;
}

void Player::update()
{
	//m_playerCamera->follow(this->getPosition());
	m_playerCamera->update();
}
