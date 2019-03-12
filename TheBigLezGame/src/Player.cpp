#include "Player.h"

Player::Player(Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	m_playerCamera = new Camera(startPos + glm::vec3(0.0f, 7.0f, 0.0f) , DYNAMIC);
	selectCharacter = character;
	prevYaw = -90;
	currentYaw = 0;
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
	m_playerCamera->update();
	glm::mat4 tempMat(1.0f);
	tempMat = glm::translate(tempMat, (m_playerCamera->getCameraPos() + glm::vec3(0.0f, -7.5f, 0.0f)));

	tempMat = glm::rotate(tempMat, -glm::radians(m_playerCamera->getYaw() + 90), glm::vec3(0.0, 1.0, 0.0));

	tempMat = glm::scale(tempMat, glm::vec3(0.6f, 0.6f, 0.6f));

	this->setMatrix(tempMat);
}
