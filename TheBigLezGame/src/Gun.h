#pragma once
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "Weapon.h"

class Gun : public Weapon {
private:
	std::string m_gunName;
	GLuint m_maxAmmo;
	GLuint m_clipSize;
public:
	Gun(const char* filename, std::string gunName, GLuint maxAmmo, GLuint clipSize);
	~Gun();

	void update() override;
};