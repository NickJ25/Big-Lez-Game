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

	Text* t_ammoCount;
	Text* t_gunName;

public:
	Gun(const char* filename, std::string gunName, GLuint maxAmmo, GLuint clipSize);
	~Gun();

	void shoot();
	void reload();
	void setMatrix(glm::mat4 newMat);
	void update() override;

	void primaryMove() override;
	void secondaryMove() override;
	void action() override;
};