#include "GameObject.h"

void GameObject::Move(glm::vec3 moveAmount)
{
	transformComponent->move(moveAmount);

	if (collisionComponent)
	{
		//cout << getPosition().z << endl;
		collisionComponent->setCollider(getPosition());
	}
}

void GameObject::Rotate(GLfloat degrees, glm::vec3 rotateAmount)
{
	transformComponent->rotate(degrees, rotateAmount);
}

glm::vec3 GameObject::getRotation()
{
	return transformComponent->getRotation();
}

void GameObject::Scale(glm::vec3 scaleAmount)
{
	transformComponent->scale(scaleAmount);
}

void GameObject::setShader(Shader * shader)
{
	objShader = shader;
	if (renderComponent != nullptr) {
		renderComponent->changeShader(shader);
	}
}

void GameObject::setAnimation(float s, float e) 
{
	if (renderComponent != nullptr) {
		renderComponent->setAnim(s, e);
	}
}

void GameObject::setPauseFrame(float p)
{
	if (renderComponent != nullptr) {
		renderComponent->setPauseFrame(p);
	}
}

void GameObject::setStill(bool s)
{
	if (renderComponent != nullptr) {
		renderComponent->setStill(s);
	}
	still = s;
}
void GameObject::setPaused(bool p)
{
	if (renderComponent != nullptr) {
		renderComponent->setPaused(p);
	}
	paused = p;
}

bool GameObject::getPaused()
{
	return paused;
}

void GameObject::setDraw(bool d)
{
	isDrawing = d;
}
glm::vec3 GameObject::getPosition()
{
	return transformComponent->getPosition();
}

void GameObject::setPosition(glm::vec3 newPos)
{
	transformComponent->setPosition(newPos);
}

glm::mat4 GameObject::getMatrix()
{
	return transformComponent->getMatrix();
}

void GameObject::setMatrix(glm::mat4 newMat)
{
	transformComponent->setMatrix(newMat);
}

void GameObject::addCollision(glm::vec3 pos, float hw, float hh)
{
	collisionComponent = new CollisionComponent(pos, hw, hh, 0.0f);
}

void GameObject::addCollision(glm::vec3 pos, float hw, float th, float hh)
{
	collisionComponent = new CollisionComponent(pos, hw, hh, th);
}

CollisionComponent* GameObject::getCollider()
{
	return collisionComponent;
}

bool GameObject::isColliderNull()
{
	if (collisionComponent) return true;
	else return false;
}

void GameObject::addController(Input::ControllerType controller)
{
	controllerComponent = new ControllerComponent(controller);
}

ControllerComponent * GameObject::getController()
{
	if (controllerComponent != nullptr) return controllerComponent;
	else return nullptr;
}

void GameObject::componentUpdate()
{

}

void GameObject::componentDraw(glm::mat4 view)
{

	if (isDrawing == true) {
		if (renderComponent != nullptr) {
			renderComponent->setDrawMatrix(transformComponent->getMatrix());
			renderComponent->setView(view);
			renderComponent->Draw();
		}
	}
	else
	{
		cout << "breakpoint" << endl;
	}
}
