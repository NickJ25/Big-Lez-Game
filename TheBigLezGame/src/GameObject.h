#pragma once
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "ControllerComponent.h"
#include "Shader.h"



using namespace std;

class GameObject {
protected:
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	ControllerComponent* controllerComponent;
	class CollisionComponent* collisionComponent = nullptr;
	glm::vec4 objPosition;
	Shader* objShader;

	bool isDrawing = true;
	bool paused = false;
	bool still = false;

public:
	GameObject(glm::vec3 pos) : objPosition(glm::vec4(pos.x, pos.y, pos.z, 1.0f)) {
		transformComponent = new TransformComponent(glm::vec4(pos,1.0f));
		renderComponent = nullptr;
		paused = false;
	}

	GameObject(glm::vec3 pos, const char* filename) : objPosition(glm::vec4(pos.x, pos.y, pos.z, 1.0f)) {
		transformComponent = new TransformComponent(objPosition);
		renderComponent = new RenderComponent(filename);
		paused = false;
	}

	GameObject( const char* filename) : objPosition(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) {
		transformComponent = new TransformComponent(objPosition);
		renderComponent = new RenderComponent(filename);
		paused = false;
	}


	void setAnimation(float s, float e);

	void setPaused(bool p);
	bool getPaused();

	void setStill(bool s);

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
	glm::vec3 getRotation();

	void setPosition(glm::vec3 newPos);
	void setMatrix(glm::mat4 newMat);
	glm::mat4 getMatrix();

	void addCollision(glm::vec3 pos, float hw, float hh);
	void addCollision(glm::vec3 pos, float hw, float th, float hh);
	CollisionComponent* getCollider();
	bool isColliderNull();

	void addController(Input::ControllerType controller);
	ControllerComponent* getController();

	void componentUpdate();
	void componentDraw(glm::mat4 view);

	void setPauseFrame(float p);
};