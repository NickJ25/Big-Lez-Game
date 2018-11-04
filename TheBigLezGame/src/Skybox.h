#pragma once
#include "GameObject.h"

class Skybox: public GameObject {
private:

public:
	Skybox(glm::mat4 objectOrientation) : GameObject(objectOrientation) {

		GameObject::addRender();
	};
	void update() override;

};