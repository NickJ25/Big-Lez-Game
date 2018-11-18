#pragma once
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "Shader.h"



using namespace std;

class GameObject {
protected:
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	glm::vec4 objPosition;
	Shader* objShader;

public:
	GameObject(glm::vec3 pos) : objPosition(glm::vec4(pos.x, pos.y, pos.z, 1.0f)) {
		transformComponent = new TransformComponent(glm::vec4(pos,1.0f));
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
	void Rotate(GLfloat degrees, glm::vec3 rotateAmount);
	void Scale(glm::vec3 scaleAmount);
	void setShader(Shader* shader);
	void componentUpdate();
	void componentDraw(glm::mat4 view);
};