#include "Player.h"

// don't render function?

Player::Player(Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	m_playerCamera = new Camera(startPos + glm::vec3(0.0f, 7.0f, 0.0f) , STATIC);
	prevYaw = -90;
	prevPos = this->getPosition();
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
	
	//cout << "currentPos: " << this->getPosition().x << " " << this->getPosition().y << " " << this->getPosition().z << endl;

	glm::vec3 tempPos = this->getPosition();
	if (Input::keyboard1.keys[GLFW_KEY_W]) {
		m_playerCamera->setCameraPos(m_playerCamera->getCameraPos() - m_playerCamera->getFront() * 1.0f);
		GameObject::Move(glm::vec3(0.0, 0.0, 1.0 * m_playerCamera->getFront().z));
		//cout << (m_playerCamera->getCameraPos() - m_playerCamera->getFront()).x << " " << (m_playerCamera->getCameraPos() - m_playerCamera->getFront()).y << " " << (m_playerCamera->getCameraPos() - m_playerCamera->getFront()).z << endl;
		//tempPos.x -= m_playerCamera->getFront().x * 1.0f;
		//this->Move(glm::vec3(-(prevPos - m_playerCamera->getCameraPos()).x, 0.0, -(prevPos - m_playerCamera->getCameraPos()).z));
		//this->setPosition(m_playerCamera->getCameraPos() - m_playerCamera->getFront());
		//tempPos.z -= m_playerCamera->getFront().z * 1.0f;
	}
	if (Input::keyboard1.keys[GLFW_KEY_S]) {
		m_playerCamera->setCameraPos(m_playerCamera->getCameraPos() + m_playerCamera->getFront() * 1.0f);
		//tempPos.x += m_playerCamera->getFront().x * 1.0f;
		//tempPos.z += m_playerCamera->getFront().z * 1.0f;
	}
	if (Input::keyboard1.keys[GLFW_KEY_K]) {
		this->Move(glm::vec3(-0.1, 0.0, 0.0));
	}
	if (Input::keyboard1.keys[GLFW_KEY_A]) {
		m_playerCamera->setCameraPos(m_playerCamera->getCameraPos() + m_playerCamera->getRight() * 1.0f);
		//tempPos.x += m_playerCamera->getRight().x * 1.0f;
		//tempPos.z += m_playerCamera->getRight().z * 1.0f;
	}
	if (Input::keyboard1.keys[GLFW_KEY_D]) {
		m_playerCamera->setCameraPos(m_playerCamera->getCameraPos() - m_playerCamera->getRight() * 1.0f);
		//tempPos.x -= m_playerCamera->getRight().x * 1.0f;
		//tempPos.z -= m_playerCamera->getRight().z * 1.0f;
		this->Move(glm::vec3(-0.1, 0.0, 0.0));
	}
	//cout << "tempPos: " << m_playerCamera->getFront().x << " " << m_playerCamera->getFront().y << " " << m_playerCamera->getFront().z << endl;
	//cout << "tempPos: " << tempPos.x << " " << tempPos.y << " " << tempPos.z << endl;
	//this->Move(glm::vec3(tempPos));
	

	
	//tempPos = glm::vec3(0.0, 0.0, 0.0);
	//glm::vec3 nowPos = prevPos - tempPos;
	//this->Move(nowPos);
	//prevPos = tempPos;

	m_playerCamera->update();
	GLfloat nowYaw = prevYaw - m_playerCamera->getYaw();
	this->Rotate(nowYaw, glm::vec3(0.0, 1.0, 0.0));
	prevYaw = m_playerCamera->getYaw();

	//m_charLabel->draw("Big Lez", colourTemp);
}
