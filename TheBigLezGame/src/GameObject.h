#pragma once
#include "RenderComponent.h"
#include "TransformComponent.h"



using namespace std;

class GameObject {
protected:
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	glm::mat4 objOrientation;
public:
	GameObject(glm::mat4 objectOrientation) : objOrientation(objectOrientation) {
		//transformComponent = new TransformComponent(objectOrientation);
	}

	virtual ~GameObject() {
		delete transformComponent;
		delete renderComponent;
	}

	virtual void update() = 0;
	void addRender();
	void componentUpdate();
	void componentDraw();
};