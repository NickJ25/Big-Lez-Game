#pragma once
#include "RenderComponent.h"
#include "TransformComponent.h"



using namespace std;

class GameObject {
protected:
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	glm::vec4 objPosition;
public:
	GameObject(glm::vec3 pos) : objPosition(glm::vec4(pos.x, pos.y, pos.z, 1.0f)) {
		transformComponent = new TransformComponent(objPosition);
	}

	GameObject(glm::vec3 pos, const char* filename) : objPosition(glm::vec4(pos.x, pos.y, pos.z, 1.0f)) {
		transformComponent = new TransformComponent(objPosition);
		renderComponent = new RenderComponent(filename);
	}

	virtual ~GameObject() {
		delete transformComponent;
		delete renderComponent;
	}

	virtual void update() = 0;
	void Move(glm::vec3 moveAmount);
	void Rotate(glm::vec3 rotateAmount);
	void Scale(glm::vec3 scaleAmount);
	void componentUpdate();
	void componentDraw();
};