#pragma once
#include "GameObject.h"

class Weapon : public GameObject {
private:

public:
	Weapon(const char* filename, glm::vec3 position) : GameObject(position, filename) {

	};

	virtual void update() = 0;

	// General weapon things.
	virtual void primaryMove(bool active) = 0;
	virtual void secondaryMove(bool active) = 0;
	virtual void action(bool active) = 0;
	virtual bool hasAttacked() = 0;
	virtual void setMatrix(glm::mat4 newMat) = 0;
	virtual void setViewport(int num) = 0;
	virtual string getName() = 0;
};