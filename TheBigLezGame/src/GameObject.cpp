#include "GameObject.h"

void GameObject::Move(glm::vec3 moveAmount)
{
	transformComponent->move(moveAmount);

	if (collisionComponent)
	{
		collisionComponent->move(moveAmount);
	}
}

void GameObject::Rotate(GLfloat degrees, glm::vec3 rotateAmount)
{
	transformComponent->rotate(degrees, rotateAmount);
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

void GameObject::addCollision(glm::vec3 pos, float hw, float hh)
{
	collisionComponent = new CollisionComponent(pos, hw, hh);
}

CollisionComponent* GameObject::getCollider()
{
	return collisionComponent;
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
