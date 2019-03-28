 #include "Player.h"

Player::Player(ControllerComponent::ControllerType controller, Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	if (controller == ControllerComponent::KEYBOARD) {
		m_playerCamera = new Camera(startPos + glm::vec3(0.0f, 4.5f, 0.0f), DYNAMIC);
	}
	else {
		m_playerCamera = new Camera(startPos + glm::vec3(0.0f, 7.0f, 0.0f), STATIC);
	}
	this->addController(controller);
	m_character = character;
	prevYaw = -90;
	currentYaw = 0;
	m_charLabel = new Text(glm::vec2(6.0f, 5.0f), "assets/Fonts/ariali.ttf");
}

Player::Player(Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	m_character = character;
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
	setAnimation(0, 8);
}

Camera* Player::getCamera()
{
	return m_playerCamera;
}

void Player::update()
{
	if (m_playerCamera) {
		m_playerCamera->update();

		// Create a matrix and apply the rotations and translations on it.
		glm::mat4 tempMat(1.0f);
		tempMat = glm::translate(tempMat, (m_playerCamera->getCameraPos() + glm::vec3(0.0f, -7.5f, 0.0f)));
		tempMat = glm::rotate(tempMat, -glm::radians(m_playerCamera->getYaw() + 90), glm::vec3(0.0, 1.0, 0.0));
		tempMat = glm::translate(tempMat, (glm::vec3(0.0f, 0.0f, -0.8f)));


		GameObject::setMatrix(tempMat);

		// Apply the same matrix to the gun model
		if (currentWeapon != NULL) {
			glm::mat4 gunMat(1.0f);
			//gunMat = glm::rotate(gunMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			gunMat = glm::translate(gunMat, (m_playerCamera->getCameraPos() + glm::vec3(0.0f, -13.0f, 0.0f)));
			gunMat = glm::rotate(gunMat, -glm::radians(m_playerCamera->getYaw() + 90), glm::vec3(0.0, 1.0, 0.0));
			gunMat = glm::rotate(gunMat, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
			//gunMat = glm::translate(gunMat, (glm::vec3(0.2f, -4.0f, 0.0f)));

			currentWeapon->setMatrix(gunMat);
			currentWeapon->update();
		}



		// Gun controls
		if (currentWeapon != NULL) {
			currentWeapon->primaryMove(this->getController()->getPrimaryAction());
			currentWeapon->secondaryMove(this->getController()->getSecondaryAction());
			currentWeapon->action(this->getController()->getReloadAction());

		}
	}
}

void Player::addWeapon(Weapon * weapon)
{
	if (m_playerInventory[0] == NULL) {
		m_playerInventory[0] = weapon;
		currentWeapon = m_playerInventory[0];
	}
	else if (m_playerInventory[1] == NULL) {
		m_playerInventory[1] = weapon;
	}
	else {
		std::cout << "Error: " << m_character.name << " inventory is full!" << std::endl;
	}
}

bool Player::hasPlayerAttacked()
{
	if (currentWeapon != NULL) {
		return currentWeapon->hasAttacked();
	}
	return false;
}
Player::Character Player::getCharacter()
{
	return m_character;
	//this->setMatrix(tempMat);
}
