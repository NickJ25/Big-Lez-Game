 #include "Player.h"

Player::Player(ControllerComponent::ControllerType controller, Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	if (controller == ControllerComponent::KEYBOARD) {
		m_playerCamera = new Camera(startPos + glm::vec3(0.0f, 7.0f, 0.0f), DYNAMIC);
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

	// Create a matrix and apply the rotations and translations on it.
	glm::mat4 tempMat(1.0f);
	tempMat = glm::translate(tempMat, (m_playerCamera->getCameraPos() + glm::vec3(0.0f, -7.5f, 0.0f)));
	tempMat = glm::rotate(tempMat, -glm::radians(m_playerCamera->getYaw() + 90), glm::vec3(0.0, 1.0, 0.0));
	tempMat = glm::translate(tempMat, (glm::vec3(0.0f, 0.0f, -0.8f)));
	tempMat = glm::scale(tempMat, glm::vec3(0.6f, 0.6f, 0.6f));

	glm::mat4 gunMat(1.0f);
	gunMat = glm::rotate(gunMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	gunMat *= glm::mat4(1.0) * tempMat;

	GameObject::setMatrix(tempMat);

	//this->Move(m_playerCamera->getCameraPos() + glm::vec3(0.0f, -8.0f, 0.0f));
	//this->Rotate(-m_playerCamera->getYaw() + 90, glm::vec3(0.0, 1.0, 0.0));
	//this->Scale(glm::vec3(0.6, 0.6, 0.6));

	// Apply the same matrix to the gun model
	if (currentWeapon != NULL) {
		currentWeapon->setMatrix(tempMat);
		currentWeapon->update();
	}

	setAnimation(0, 120);

	// Gun controls
	if (currentWeapon != NULL) {
		currentWeapon->primaryMove(this->getController()->getPrimaryAction());
		currentWeapon->secondaryMove(this->getController()->getSecondaryAction());
		currentWeapon->action(this->getController()->getReloadAction());

	}
	//cout << Input::mouse1.buttons[GLFW_MOUSE_BUTTON_LEFT] << endl;
	//if (Input::mouse1.buttons[GLFW_MOUSE_BUTTON_LEFT]) {
	//	if (currentWeapon != NULL) {
	//		currentWeapon->primaryMove();
	//	}
	//}
	//if (Input::mouse1.buttons[GLFW_MOUSE_BUTTON_RIGHT]) {
	//	if (currentWeapon != NULL) {
	//		currentWeapon->secondaryMove();
	//	}
	//}
	//if (Input::keyboard1.keys[GLFW_KEY_R]) {
	//	if (currentWeapon != NULL) {
	//		currentWeapon->action();
	//	}
	//}
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

Player::Character Player::getCharacter()
{
	return m_character;
}
