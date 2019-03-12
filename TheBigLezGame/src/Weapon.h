#pragma once
#include "GameObject.h"

class Weapon : public GameObject {
private:

public:
	Weapon(const char* filename, glm::vec3 position) : GameObject(position, filename) {

	};

	virtual void update() = 0;
};