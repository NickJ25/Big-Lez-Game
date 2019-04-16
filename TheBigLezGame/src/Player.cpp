 #include "Player.h"

Player::Player(Input::ControllerType controller, Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{
	if (controller == Input::KEYBOARD) {
		m_playerCamera = new Camera(startPos, KEYBOARD);
	}
	else {
		m_playerCamera = new Camera(startPos, CONTROLLER);
	}
	//this->addCollision(startPos, 50, 50);
	this->addController(controller);
	m_character = character;
	prevYaw = -90;
	currentYaw = 0;
	m_charLabel = new Text(glm::vec2(6.0f, 5.0f), "assets/Fonts/ariali.ttf");

	//initialise animation storage
	runAnim = { 0, 0 };
	deathAnim = { 0,0 };
	stillAnim = { 0,0 };
	deathStillAnim = 0;

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
	deathAnim = { 0,0 };
	stillAnim = { 0,0 };
	deathStillAnim = 0;

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


		float deltaTime = currentTime - previousTime;
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

	currentTime = glfwGetTime();
	float deltaTime = currentTime - previousTime;
	previousTime = currentTime;

	//check for injuries or death
	if (isDead == true) {
		if (deathAnimSet == false) {
			setAnimation(deathAnim.first, deathAnim.second);
			deathAnimSet = true;
		}
		if (deathTimer <= 0)
		{
			setStill(true);
			still = true;
			setPauseFrame(deathStillAnim);
		}
		else
		{
			deathTimer -= deltaTime;
		}
	}
	else {
		//Movement controls
		cout << "Player Pos: " << m_playerCamera->getCameraPos().x << " " << m_playerCamera->getCameraPos().z << endl;
		m_playerCamera->setCameraPos(m_playerCamera->getCameraPos() + cameraOffset);
		glm::vec3 tempPos = m_playerCamera->getCameraPos();
		if (this->getController()->getForwardMovement()) {
			tempPos = m_playerCamera->getCameraPos() - m_playerCamera->getCameraFront() * 1.0f;
			tempPos.y = 0;
			isMoving = true;
			setAnimation(runAnim.first, runAnim.second);
		}
		if (this->getController()->getBackMovement()) {
			tempPos = m_playerCamera->getCameraPos() + m_playerCamera->getCameraFront() * 1.0f;
			tempPos.y = 0;
			isMoving = true;
			setAnimation(runAnim.first, runAnim.second);
		}
		if (this->getController()->getLeftMovement()) {
			tempPos = m_playerCamera->getCameraPos() + glm::normalize(glm::cross(m_playerCamera->getCameraFront(), glm::vec3(0.0f, 1.0f, 0.0f))) * 1.0f;
			tempPos.y = 0;
			isMoving = true;
			setAnimation(runAnim.first, runAnim.second);
		}
		if (this->getController()->getRightMovement()) {
			tempPos = m_playerCamera->getCameraPos() - glm::normalize(glm::cross(m_playerCamera->getCameraFront(), glm::vec3(0.0f, 1.0f, 0.0f))) * 1.0f;
			tempPos.y = 0;
			//m_playerCamera->setCameraPos(tempPos);
			isMoving = true;
			setAnimation(runAnim.first, runAnim.second);
		}
		else
		{
			isMoving = false;
			setAnimation(stillAnim.first, stillAnim.second);
		}
		//m_playerCamera->setCameraPos(tempPos);

		
		m_playerCamera->update();

		// Create a matrix and apply the rotations and translations on it.
		glm::mat4 tempMat(1.0f);
		//tempMat = glm::translate(tempMat, (m_playerCamera->getCameraPos() + glm::vec3(0.0f, -15.0f, 0.0f))); //-7.5

		//if(previousMovement == glm::vec3(0.0f, 0.0f, 0.0f))
		//	previousMovement = m_playerCamera->getCameraPos() + glm::vec3(0.0f, -15.0f, 0.0f);
		//else
		//	previousMovement -= m_playerCamera->getCameraPos() + glm::vec3(0.0f, -15.0f, 0.0f);

		tempMat = glm::translate(tempMat, (tempPos + glm::vec3(0.0f, -14.0f, 0.0f)));
		tempMat = glm::rotate(tempMat, -glm::radians(m_playerCamera->getYaw() + 90), glm::vec3(0.0, 1.0, 0.0));
		tempMat = glm::translate(tempMat, (glm::vec3(0.0f, 0.0f, -0.8f)));


		GameObject::setMatrix(tempMat);
		m_playerCamera->setCameraPos(tempPos - cameraOffset);

		//move the collider alongside the player
		collisionComponent->setCollider(m_playerCamera->getCameraPos());

		// Apply the same matrix to the gun model
		if (currentWeapon != nullptr) {
			glm::mat4 gunMat(1.0f);
			//gunMat = glm::rotate(gunMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			gunMat = glm::translate(gunMat, (m_playerCamera->getCameraPos() + glm::vec3(0.0f, -9.0f, 0.0f)));
			gunMat = glm::rotate(gunMat, -glm::radians(m_playerCamera->getYaw() + 90), glm::vec3(0.0, 1.0, 0.0));
			gunMat = glm::rotate(gunMat, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
			gunMat = glm::scale(gunMat, glm::vec3(0.8, 0.8, 0.8));
			gunMat = glm::translate(gunMat, (glm::vec3(0.2f, -2.0f, 0.0f)));

			currentWeapon->setMatrix(gunMat);
			currentWeapon->update();
		}

		// Gun controls
		if (currentWeapon != nullptr) {
			currentWeapon->setViewport(m_playerNum);
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
		deathAnim.first = s, deathAnim.second = e;
	}
	if (type == 2) {
		stillAnim.first = s, stillAnim.second = e;
	}
	if (type == 3) {
		deathStillAnim = s;
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

	if (health <= 0)
	{
		health = 0;
		isDead = true;
	}
}

void Player::gainPoints(int p)
{
	points += p;
}

glm::vec3 Player::getPreviousPosition()
{
	return previousMovement;
}
void Player::setPlayerNum(int playerNum)
{
	m_playerNum = playerNum;
}
