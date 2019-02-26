#include "Player.h"

Player::Player(Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	m_playerCamera = new Camera(startPos + glm::vec3(0.0f, 6.0f, 1.0f) , DYNAMIC);
	prevYaw = -90;
	
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
	//m_playerCamera->follow();
	m_playerCamera->update();
	GLfloat nowYaw = prevYaw - m_playerCamera->getYaw();
	this->Rotate(nowYaw, glm::vec3(0.0, 0.0, 1.0));
	prevYaw = m_playerCamera->getYaw();
}
