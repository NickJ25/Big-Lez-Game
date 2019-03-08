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
	class CollisionComponent* collisionComponent;
	glm::vec4 objPosition;
	Shader* objShader;

	bool isDrawing = true;

public:
	GameObject(glm::vec3 pos) : objPosition(glm::vec4(pos.x, pos.y, pos.z, 1.0f)) {
		transformComponent = new TransformComponent(glm::vec4(pos,1.0f));
	}

	GameObject(glm::vec3 pos, const char* filename) : objPosition(glm::vec4(pos.x, pos.y, pos.z, 1.0f)) {
		transformComponent = new TransformComponent(objPosition);
		renderComponent = new RenderComponent(filename);
	}

	GameObject( const char* filename) : objPosition(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) {
		transformComponent = new TransformComponent(objPosition);
		renderComponent = new RenderComponent(filename);
	}

	void setAnimation(float s, float e);

	virtual ~GameObject() {
		delete transformComponent;
		delete renderComponent;
	}

	virtual void update() = 0;
	void Move(glm::vec3 moveAmount);
	void Rotate(GLfloat degrees, glm::vec3 rotateAmount);
	void Scale(glm::vec3 scaleAmount);
	void setShader(Shader* shader);
	void setDraw(bool d);

	glm::vec3 getPosition();

	void addCollision(glm::vec3 pos, float hw, float hh);
	CollisionComponent* getCollider();

	void componentUpdate();
	void componentDraw(glm::mat4 view);
};