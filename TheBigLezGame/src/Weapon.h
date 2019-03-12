#pragma once
#include "GameObject.h"

class Weapon : public GameObject {
private:

public:
	Weapon(const char* filename, glm::vec3 position) : GameObject(position, filename) {

	};

	virtual void update() = 0;

	// General weapon things.
	virtual void primaryMove() = 0;
	virtual void secondaryMove() = 0;
	virtual void action() = 0;
	virtual void setMatrix(glm::mat4 newMat) = 0;
};