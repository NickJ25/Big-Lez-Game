#pragma once
#include "GameObject.h"

class Light : public GameObject {
private:

public:
	Light(glm::vec3 position) : GameObject(position) {

	};
	virtual void update() = 0;
};