 #include "Player.h"

Player::Player(Input::ControllerType controller, Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	if (controller == Input::KEYBOARD) {
		m_playerCamera = new Camera(startPos + glm::vec3(0.0f, 0.0f , 0.0f), KEYBOARD); //4.5f
	}
	else {
		m_playerCamera = new Camera(startPos + glm::vec3(0.0f, 4.5f, 0.0f), CONTROLLER);
	}
	this->addController(controller);
	m_character = character;
	prevYaw = -90;
	currentYaw = 0;
	m_charLabel = new Text(glm::vec2(6.0f, 5.0f), "assets/Fonts/ariali.ttf");

	//initialise animation storage
	runAnim = { 0, 0 };
	injuryAnim = { 0,0 };
	deathAnim = { 0,0 };
	stillAnim = { 0,0 };

	//set default health and armour to prevent crashes
	health = 100;
	armour = 1;
}

Player::Player(Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	m_character = character;
	prevYaw = -90;
	currentYaw = 0;
	m_charLabel = new Text(glm::vec2(6.0f, 5.0f), "assets/Fonts/ariali.ttf");

	//initialise animation storage
	runAnim = { 0, 0 };
	injuryAnim = { 0,0 };
	deathAnim = { 0,0 };
	stillAnim = { 0,0 };

	//set default health and armour to prevent crashes
	health = 100;
	armour = 1;
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

void Player::playSound(int sound, float delay)
{
	if (playingSound == false && delay != 100.0f)
	{
		soundDelay = delay;
		playingSound = true;
	}
	if(playingSound == true){


		currentTime = glfwGetTime();
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		soundDelay -= deltaTime;
		if (soundDelay <= 0)
		{
			if (soundCalled == false) {
				privateEngine->setSoundVolume(1.0f);
				privateEngine->play2D(getSound(sound));//, irrklang::vec3df(getPosition().x, getPosition().y, getPosition().z));
				soundCalled = true;
			}
			if (soundAnimSet == false) {
				soundAnimationTime = getSound(sound)->getPlayLength()/1000;
				soundAnimSet = true;
			}
			if (soundAnimationTime > 0 && soundAnimSet == true)
			{

				soundAnimationTime -= deltaTime;

				if(isMoving == true)
					//universal walking - talking animation
					setAnimation(0.0f, 1.0f);
				else
					//universal talking only animation
					setAnimation(0.0f, 1.0f);
			}
			if (soundAnimationTime <= 0) {
				soundAnimSet = false;
				playingSound = false;
				soundCalled = false;
			}
		}
	}
}

void Player::update()
{
	//updates the timer without setting a new sound
	playSound(0, 100.0f);

	//check for injuries or death
	if (isDead == true) {

	}
	else {
		//Movement controls
		if (this->getController()->getForwardMovement()) {
			glm::vec3 tempPos = m_playerCamera->getCameraPos() - m_playerCamera->getCameraFront() * 1.0f;
			tempPos.y = 0;
			m_playerCamera->setCameraPos(tempPos);
			isMoving = true;
			setAnimation(runAnim.first, runAnim.second);
		}
		else
			if (this->getController()->getBackMovement()) {
				glm::vec3 tempPos = m_playerCamera->getCameraPos() + m_playerCamera->getCameraFront() * 1.0f;
				tempPos.y = 0;
				m_playerCamera->setCameraPos(tempPos);
				isMoving = true;
				setAnimation(runAnim.first, runAnim.second);
			}
			else
				if (this->getController()->getLeftMovement()) {
					glm::vec3 tempPos = m_playerCamera->getCameraPos() + glm::normalize(glm::cross(m_playerCamera->getCameraFront(), glm::vec3(0.0f, 1.0f, 0.0f))) * 1.0f;
					tempPos.y = 0;
					m_playerCamera->setCameraPos(tempPos);
					isMoving = true;
					setAnimation(runAnim.first, runAnim.second);
				}
				else
					if (this->getController()->getRightMovement()) {
						glm::vec3 tempPos = m_playerCamera->getCameraPos() - glm::normalize(glm::cross(m_playerCamera->getCameraFront(), glm::vec3(0.0f, 1.0f, 0.0f))) * 1.0f;
						tempPos.y = 0;
						m_playerCamera->setCameraPos(tempPos);
						isMoving = true;
						setAnimation(runAnim.first, runAnim.second);
					}
					else
					{
						isMoving = false;
						setAnimation(stillAnim.first, stillAnim.second);
					}


		m_playerCamera->update();

		// Create a matrix and apply the rotations and translations on it.
		glm::mat4 tempMat(1.0f);
		tempMat = glm::translate(tempMat, (m_playerCamera->getCameraPos() + glm::vec3(0.0f, -15.0f, 0.0f))); //-7.5
		tempMat = glm::rotate(tempMat, -glm::radians(m_playerCamera->getYaw() + 90), glm::vec3(0.0, 1.0, 0.0));
		tempMat = glm::translate(tempMat, (glm::vec3(0.0f, 0.0f, -0.8f)));


		GameObject::setMatrix(tempMat);

		//move the collider alongside the player
		collisionComponent->setCollider(m_playerCamera->getCameraPos());

		// Apply the same matrix to the gun model
		if (currentWeapon != nullptr) {
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
		if (currentWeapon != nullptr) {
			currentWeapon->primaryMove(this->getController()->getPrimaryAction());
			currentWeapon->secondaryMove(this->getController()->getSecondaryAction());
			currentWeapon->action(this->getController()->getReloadAction());

		}
	}
}


void Player::addWeapon(Weapon * weapon)
{
	if (m_playerInventory[0] == nullptr) {
		m_playerInventory[0] = weapon;
		currentWeapon = m_playerInventory[0];
	}
	else if (m_playerInventory[1] == nullptr) {
		m_playerInventory[1] = weapon;
	}
	else {
		std::cout << "Error: " << m_character.name << " inventory is full!" << std::endl;
	}
}

bool Player::hasPlayerAttacked()
{
	if (currentWeapon != nullptr) {
		return currentWeapon->hasAttacked();
	}
	return false;
}
Player::Character Player::getCharacter()
{
	return m_character;
}

void Player::setSound(irrklang::ISoundSource* newSound)
{
	sounds.push_back(newSound);
}

irrklang::ISoundSource* Player::getSound(int sound)
{
	return sounds.at(sound);
}

void Player::setAnimationCalls(float s, float e, int type)
{
	if (type == 0) {
		runAnim.first = s, runAnim.second = e;
	}
	if (type == 1) {
		injuryAnim.first = s, injuryAnim.second = e;
	}
	if (type == 2) {
		deathAnim.first = s, deathAnim.second = e;
	}
}

void Player::setCharacterAttributes(float h, float a)
{
	health = h;
	armour = a;
}

void Player::takeDamage(float damage)
{
	health = damage / armour;
	if(isInjured == false)
	isInjured = true;

	if (health <= 0)
	{
		health = 0;
		isDead = true;
	}
}