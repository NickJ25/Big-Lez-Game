#pragma once
//std library
#include <iostream>
#include <string>

//glm
#include "glm/glm.hpp"

//glew
#include "GL/glew.h"

//other files
#include "Weapon.h"
#include "Text.h"
#include "Image.h"

class Gun : public Weapon {
private:
	std::string m_gunName;
	GLuint m_maxAmmo;
	GLuint m_clipSize;
	GLuint m_currentClip = m_clipSize;
	float m_shootDelay;

	bool sprayAllowed;
	bool gunFired;
	float lastFired = glfwGetTime();
	bool alreadyFired = false;
	Text* t_ammoCount;
	Text* t_gunName;
	Image* i_crosshair;

public:
	Gun(const char* filename, std::string gunName, GLuint maxAmmo, GLuint clipSize, 
		float shootDelay, bool allowSpray);
	~Gun();

	void shoot(bool clicked);
	void reload(bool clicked);
	void setMatrix(glm::mat4 newMat);
	void update() override;
	void checkHit();

	void primaryMove(bool active) override;
	void secondaryMove(bool active) override;
	void action(bool active) override;
	bool hasAttacked() override;
};