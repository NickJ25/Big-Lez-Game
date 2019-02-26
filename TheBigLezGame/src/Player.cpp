#include "Player.h"

Player::Player(Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	m_playerCamera = new Camera(startPos + glm::vec3(0.0f, 7.0f, 0.0f) , DYNAMIC);
	prevYaw = -90;
	prevPos = m_playerCamera->getCameraPos();
	m_charLabel = new Text(glm::vec2(6.0f, 5.0f), "assets/Fonts/ariali.ttf");
	
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
	glm::vec3 nowPos = prevPos - m_playerCamera->getCameraPos;
	this->Move(nowPos);
	prevPos = pos;

	m_playerCamera->update();
	GLfloat nowYaw = prevYaw - m_playerCamera->getYaw();
	this->Rotate(nowYaw, glm::vec3(0.0, 0.0, 1.0));
	prevYaw = m_playerCamera->getYaw();

	//m_charLabel->draw("Big Lez", colourTemp);
}
