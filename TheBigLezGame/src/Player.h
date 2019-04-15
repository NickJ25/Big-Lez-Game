#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Weapon.h"
#include "Text.h"
#include <iostream>
#include <string>
#include "Input.h"
#include <irrKlang.h>

class Player : public GameObject
{
public:
	struct Character {
		int id;
		std::string name;
		std::string fileLocation;
		bool isLocked = false;		// Not locked by default
		GLint health;
		GLint walkSpeed;
		Input::ControllerType control;
	};

	Player(Input::ControllerType controller, Character character, glm::vec3 startPos);
	Player(Character character, glm::vec3 startPos);
	~Player();

	void playAnimation();
	Camera* getCamera();
	void update() override;
	void addWeapon(Weapon* weapon);
	bool hasPlayerAttacked();
	
	Player::Character getCharacter();

	//sound stuff
	void setSound(irrklang::ISoundSource*);
	irrklang::ISoundSource* getSound(int sound);

	//plays selected sound
	void playSound(int sound, float delay = 100.0f);

	//sets animation to storage pairs
	void setAnimationCalls(float s, float e, int type);

	void setCharacterAttributes(float h, float a);

	void takeDamage(float damage);

private:
	//health
	float health;
	float armour;

	//animation storage
	std::pair<float, float> runAnim;
	std::pair<float, float> injuryAnim;
	std::pair<float, float> deathAnim; 
	std::pair<float, float> stillAnim;

	//animation timers
	float deathTimer = 3.0f;
	//animation control variables
	bool isInjured = false;
	bool isDead = false;

	irrklang::ISoundEngine *privateEngine = irrklang::createIrrKlangDevice();
	float soundDelay;
	bool playingSound = false;
	bool soundCalled = false;

	float soundAnimationTime = 0.0f;
	bool soundAnimSet = false;

	bool isMoving = false;

	vector<irrklang::ISoundSource*> sounds;

	Character m_character;
	Camera* m_playerCamera;
	Text* m_charLabel;
	Weapon* m_playerInventory[2] = { nullptr, nullptr };
	Weapon* currentWeapon = nullptr;

	GLfloat prevYaw, currentYaw;

	GLuint m_health;

	glm::vec3 colourTemp = glm::vec3(0.2, 0.4, 0.5);

	bool playerShootGun = false;

	float currentTime = 0.0f;
	float previousTime = 0.0f;


};

// Make camera unique
// Make array to hold multiple players
