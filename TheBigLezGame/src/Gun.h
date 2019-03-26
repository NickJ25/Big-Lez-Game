#pragma once
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "Weapon.h"
#include "Text.h"

class Gun : public Weapon {
private:
	std::string m_gunName;
	GLuint m_maxAmmo;
	GLuint m_clipSize;
	GLuint m_currentClip = m_clipSize;

	bool sprayAllowed;
	bool gunFired;
	bool alreadyFired = false;;
	Text* t_ammoCount;
	Text* t_gunName;

public:
	Gun(const char* filename, std::string gunName, GLuint maxAmmo, GLuint clipSize, bool allowSpray);
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